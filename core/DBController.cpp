
#include "DBController.hpp"

#include "Files.hpp"


DBController::DBController()
: serverUsers_(nullptr), clientUsers_(nullptr) 
{
	//
}

DBController::DBController(ServerUsers *su)
: serverUsers_(su), clientUsers_(nullptr) 
{
	//
}


DBController::DBController(ClientUsers *cu)
: serverUsers_(nullptr), clientUsers_(cu)
{
	//
}


DBController::ConvIter DBController::findConversation(const String& u1, const String& u2)
{
	auto it = conversations_.begin();
	for (; it != conversations_.end(); ++it) {
		if (it->equal(u1, u2)) {
			return it;
		}
	}
	return it;
}

void DBController::addMessage(const String& u1, const String& u2, const String& msg)
{
	mutGuard mg(mutex_);
	auto it = findConversation(u1, u2);
	if (it == conversations_.end()) {
		Conversation c(u1, u2);
		c.addMessage(msg);
		conversations_.push_back(c);
	} else {
		it->addMessage(msg);
	}
}

void DBController::addPendingMessage(const String& u, const String& msg)
{
	mutGuard mg(mutex_);
	const String file = Files::PMsgDir + u + Files::fileType;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	ofile.write(msg.c_str(), msg.size());
	ofile.write("\n", 1);
	ofile.close();
}

void DBController::addPMsgsToConv(const String& u)
{
	//mutGuard mg(mutex_);
	const String pMessages = Files::PMsgDir + u + Files::fileType;
	std::ifstream ifile(pMessages, std::fstream::in);
	String fromUser;
	String msg;
	if (!ifile.is_open()) {
		return;
	}
	while (std::getline(ifile, msg)) {
		fromUser = extractWord_(msg, false);
		addMessage(u, fromUser, msg);
	}
	clearPMessages(u);
}

void DBController::clearPMessages(const String& u)
{
	mutGuard mg(mutex_);
	const String file = Files::PMsgDir + u + Files::fileType;
	std::ofstream ofile(file, std::ofstream::trunc);
	ofile.close();
}

DBController::PMessagesPtr DBController::getPMessages(const String& u)
{
	mutGuard mg(mutex_);
	const String file = Files::PMsgDir + u + Files::fileType;
	std::ifstream ifile(file, std::fstream::in);
	PMessagesPtr pm(new PMessages);
	if (ifile.is_open()) {
		String msg;
		while (std::getline(ifile, msg)) {
			pm->push_back(msg);
		}
	}
	return pm;
}


DBController::ConvPtr DBController::getConversation(const String& u1, const String& u2)
{
	//???????
	auto it = findConversation(u1, u2);
	if (it == conversations_.end()) {
		return ConvPtr();
	}
	return it->getConversation();
}


void DBController::addUser(ServerUser& u)
{
	mutGuard mg(mutex_);
	const String file = Files::ServerUsersDir + Files::usersFile;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	String s = u.toStringLog() + "\n";
	ofile.write(s.c_str(), s.size());
	ofile.close();
}

void DBController::getUsers()
{
	mutGuard mg(mutex_);
	const String file = Files::ServerUsersDir + Files::usersFile;
	std::ifstream ifile(file, std::fstream::in);
	String s;
	while (std::getline(ifile, s)) {
		ServerUser u;
		u.fromString(s);
		serverUsers_->insert(u);
	}
	ifile.close();
}


void DBController::logServer(const String& str)
{
	mutGuard mg(mutex_);
	const String file = Files::ServerLogDir + Files::logFile;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	ofile.write(str.c_str(), str.size());
	ofile.write("\n", 1);
	ofile.close();
}


void DBController::logClient(const String& str)
{
	mutGuard mg(mutex_);
	const String file = Files::ClientLogDir + Files::logFile;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	ofile.write(str.c_str(), str.size());
	ofile.write("\n", 1);
	ofile.close();
}


void DBController::logUsers()
{
	mutGuard mg(mutex_);
	String ps = ".............All clients are........\n...Number of clients: ";

	if (clientUsers_ != nullptr)	{
		const String file = Files::ClientLogDir + Files::usersFile;
		std::ofstream ofile(file, std::fstream::out | std::fstream::app);
		ps += std::to_string(clientUsers_->size()) + "........\n";
		ofile.write(ps.c_str(), ps.size());
		String s;
		for (auto it = clientUsers_->begin(); it != clientUsers_->end(); ++it) {
			ClientUser* p = it->getPointer();
			s = p->toString() + '\n';
			ofile.write(s.c_str(), s.size());
		}
		ps = "..............end of the list............\n\n";
		ofile.write(ps.c_str(), ps.size());
		ofile.close();
	}
	if (serverUsers_ != nullptr) {
		const String file = Files::ServerLogDir + Files::usersFile;
		std::ofstream ofile(file, std::fstream::out | std::fstream::app);
		ps += std::to_string(serverUsers_->size()) + ".........\n";
		ofile.write(ps.c_str(), ps.size());
		String s;
		for (auto it = serverUsers_->begin(); it != serverUsers_->end(); ++it) {
			ServerUser* p = it->getPointer();
			s = p->toStringLog() + '\n';
			ofile.write(s.c_str(), s.size());
		}
		ps = "..............end of the list............\n\n";
		ofile.write(ps.c_str(), ps.size());
		ofile.close();
	}
}
