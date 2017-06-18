
#include "DBController.hpp"

#include "Files.hpp"



DBController::DBController()
: serverUsers(nullptr)//, clientUsers(nullptr) 
{
	//
}

DBController::DBController(ServerUsers *su)
: serverUsers(su)//, clientUsers(nullptr) 
{
	//
}

/*
DBController::DBController(ClientUsers *cu)
: serverUsers(nullptr), clientUsers(cu)
{
	//
}
*/


DBController::ConvIter DBController::findConversation(const String& u1, const String& u2)
{
	auto it = conversations.begin();
	for (; it != conversations.end(); ++it) {
		if (it->equal(u1, u2)) {
			return it;
		}
	}
	return it;
}

void DBController::addMessage(const String& u1, const String& u2, const String& msg)
{
	mutGuard mg(mutex);

	auto it = findConversation(u1, u2);
	if (it == conversations.end()) {
		Conversation c(u1, u2);
		c.addMessage(msg);
		conversations.push_back(c);
	} else {
		it->addMessage(msg);
	}
}

void DBController::addPendingMessage(const String& u, const String& msg)
{
	String file = Files::PMsgDir + u + Files::fileType;
	mutGuard mg(mutex);
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	ofile.write(msg.c_str(), msg.size());
	ofile.write("\n", 1);
	ofile.close();
}

void DBController::addPMsgsToConv(const String& u)
{
	String pMessages = Files::PMsgDir + u + Files::fileType;
	//mutGuard mg(mutex);
	std::ifstream ifile(pMessages, std::fstream::in);
	String fromUser;
	String msg;
	if (!ifile.is_open()) {
		return;
	}
	while (std::getline(ifile, msg)) {
		fromUser = extractWord(msg, false);
		addMessage(u, fromUser, msg);
	}
	clearPMessages(u);
}

void DBController::clearPMessages(const String& u)
{
	mutGuard mg(mutex);
	String file = Files::PMsgDir + u + Files::fileType;
	std::ofstream ofile(file, std::ofstream::trunc);
	ofile.close();
}

DBController::PendingMessagesPtr DBController::getPMessages(const String& u)
{
	mutGuard mg(mutex);
	String file = Files::PMsgDir + u + Files::fileType;
	std::ifstream ifile(file, std::fstream::in);
	PendingMessagesPtr pm(new PendingMessages);
	if (ifile.is_open()) {
		String msg;
		while (std::getline(ifile, msg)) {
			pm->push_back(msg);
		}
	}
	return pm;
}


void DBController::addUser(ServerUser& u)
{
	mutGuard mg(mutex);
	String file = Files::ServerUsersDir + Files::usersFile;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	String s = u.toStringLog() + "\n";
	ofile.write(s.c_str(), s.size());
	ofile.close();
}

void DBController::getUsers()
{
	String usersFile = Files::ServerUsersDir + Files::usersFile;
	std::ifstream ifile(usersFile, std::fstream::in);
	String s;
	while (std::getline(ifile, s)) {
		ServerUser u;
		u.fromString(s);
		serverUsers->insert(u);
	}
	ifile.close();
}


void DBController::logServer(const String& str)
{
	mutGuard mg(mutex);
	std::ofstream ofile(Files::ServerLogDir + Files::logFile, std::fstream::binary 
			| std::fstream::out | std::fstream::app);
	ofile.write(str.c_str(), str.size());
	ofile.write("\n", 1);
	ofile.close();
}

/*
void DBController::logClient(const String& str)
{
	mutGuard mg(mutex);
	std::ofstream ofile(Files::ClientLogDir + Files::logFile,
			std::fstream::binary | std::fstream::out | std::fstream::app);
	ofile.write(str.c_str(), str.size());
	ofile.write("\n", 1);
	ofile.close();
}
*/

void DBController::logUsers()
{
	mutGuard mg(mutex);
	String ps = ".............All clients are........\n...Number of clients: ";

	/*if (clientUsers != nullptr)	{
		std::ofstream ofile(Files::ClientLogDir + Files::usersFile, 
				std::fstream::binary | std::fstream::out | std::fstream::app);
		ps += std::to_string(clientUsers->size()) + "........\n";
		ofile.write(ps.c_str(), ps.size());
		String s;
		for (auto it = clientUsers->begin(); it != clientUsers->end(); ++it) {
			ClientUser* p = it->getPointer();
			s = p->toString() + '\n';
			ofile.write(s.c_str(), s.size());
		}
		ps = "..............end of the list............\n\n";
		ofile.write(ps.c_str(), ps.size());
		ofile.close();
	}*/
	if (serverUsers != nullptr) {
		std::ofstream ofile(Files::ServerLogDir + Files::usersFile, 
				std::fstream::binary | std::fstream::out | std::fstream::app);
		ps += std::to_string(serverUsers->size()) + ".........\n";
		ofile.write(ps.c_str(), ps.size());
		String s;
		for (auto it = serverUsers->begin(); it != serverUsers->end(); ++it) {
			ServerUser* p = it->getPointer();
			s = p->toStringLog() + '\n';
			ofile.write(s.c_str(), s.size());
		}
		ps = "..............end of the list............\n\n";
		ofile.write(ps.c_str(), ps.size());
		ofile.close();
	}
}
