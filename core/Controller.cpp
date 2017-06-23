#include "Controller.hpp"

#include "../gui/LoginWindow.hpp"
#include "../gui/MainWindow/MainWindow.hpp"
#include "../gui/PopError.hpp"

#include "MessageTypes.hpp"

#include <iostream>


Controller::Controller(Client& c)
	: c_(c)
	, loginWindow_(nullptr)
	, mainWindow_(nullptr)
	, popError_(new PopError())
	, dbcontroller_(&users_)
{
	loginWindow_ = new LoginWindow(*this);
	mainWindow_ = new MainWindow(*this);
}

void Controller::run(const String& s)
{
	login = s;
	//std::cout << "login=" << login << ".\n";
	c_.connectServer();
	loginWindow_->showWindow();

	std::shared_ptr<pthread_t> th(new pthread_t);
	if (pthread_create(&(*th), NULL, ::handleSession, this)) {
		std::cout << "An error occurred during thread creation process.";
		return;
	}
}

String Controller::getLogin() const
{
	return userLogin_;
}

void Controller::closeConnection()
{
	c_.closeConnection();
}

void Controller::handleSession()
{
	inReaderPtr.reset(new InputReader(*this));
	inReaderPtr->startRead();
	String message;
	try {

		while (c_.recvMessage(transportLayer_) == SUCCESS) {
			for (auto p : transportLayer_) {
				processMessage(*p);
			}
			transportLayer_.clear();
		}
	} catch (const Error& err) {
		std::cout << err.what() << std::endl;
	}
	inReaderPtr->stopRead();
	c_.closeConnection();
}

String Controller::sendLoginRequest(const String& login, const String& password)
{
	userLogin_ = login;
	String msg = login + delim + password + delim;
	return "Login request: " + sendMessage(msg, loginRequest);
}

String Controller::sendLogoutRequest()
{
	String msg = "This is a logout request.";
	return "Logout request: " + sendMessage(msg, logoutRequest);
}

String Controller::sendRegistrationRequest(const String& login, const String& name,
			const String& surname, const String& password)
{
	String msg = login + delim + name + delim + surname
			+ delim + offline + delim + password + delim;
            std::cout << "Sending reg request" << std::endl;
	return "Registration request: " + sendMessage(msg, registrationRequest);
}

String Controller::sendMessageToUser(const String& toUser, String& msg)
{
	if (msg.size() == 0) {
		return emptyMessage;
	}
	auto it = find(toUser);
	if (it == users_.end()) {
		throw Error("Attempting to send a message to an unknown user.");
	}
	msg = toUser + delim + msg;
	msg = userLogin_ + delim + msg;
	return "Message to Client " + toUser + ": " + sendMessage(msg, plainMessage);
}


String Controller::sendConvRequest(const String& uLogin)
{
	String msg = userLogin_ + delim + uLogin + delim + "Conversation Request";
	return "Conversation Request: " + sendMessage(msg, convRequest);
}

String Controller::sendUserListRequest()
{
	String msg = "This is a user list request.";
	return "Client List request: " + sendMessage(msg, userListRequest);
}

String Controller::sendPendingMessagesRequest()
{
	String msg = "This is a pending messages request.";
	return "Pending Messages Request: " + sendMessage(msg, pendingMessagesRequest);
}


String Controller::sendMessage(String& message, const String& msgType)
{
	message = msgType + delim + message;
	message = std::to_string(message.size()) + delim + message; 

	if (c_.sendMessage(message) == SUCCESS) {
		return success + "message to Server sent.";
	}
	else {
		return error + " occurred during sending message to Server.\n";
	}
}

void Controller::processMessage(String& message)
{
	dbcontroller_.log(message);	
	String msgType = wordExtractor_(message);
	if (msgType == plainMessage) {
		processPlainMessage(message);
	} else if (msgType == loginRespond) {
		processLoginRespond(message);
	} else if (msgType == logoutRespond) {
		processLogoutRespond(message);
	} else if (msgType == registrationRespond) {
		processRegistrationRespond(message);
	} else if (msgType == userChangedRespond) {
		processUserChangedRespond(message);
	} else if (msgType == userListRespond) {
		processUserListRespond(message);
	} else if (msgType == convRespond) {
		processConvRespond(message);
	} else {
		String log = "Unknown type: " + msgType + " message: " + message;
		dbcontroller_.log(log);
		throw Error(log);
	}
}

void Controller::processPlainMessage(String& message)
{
	dbcontroller_.log(message);
	std::cout << message << std::endl;
	String fromUser = wordExtractor_(message);
	auto it = find(fromUser);
	if (it == users_.end()) {
		throw Error("The message is from unknown user");
	} else {
		it->addMessage(message);
		updateMainWindow(it);
	}
}

void Controller::processLoginRespond(String& message)
{
	dbcontroller_.log(message);
	std::cout << message << std::endl;
	String result = wordExtractor_(message);
	if (result == error) {
		popError_->setText(message);
		popError_->execute();
	} else {
		sendUserListRequest();
		if (loginWindow_ != nullptr) {
			//delete loginWindow_;
			//loginWindow_ = nullptr;
			//loginWindow_->hide();
		}
		sleep(1);
		if (mainWindow_ != nullptr) {
			mainWindow_->showWindow();
		} else {
			throw Error("Error: MainWindow == nullptr");
		}
		sendPendingMessagesRequest();
	}
}

void Controller::processLogoutRespond(String& message)
{
	String result = wordExtractor_(message);
	dbcontroller_.log(message);
	std::cout << message << std::endl;
	if (result == error) {
		popError_->setText(message);
		popError_->execute();
	} else {
		if (mainWindow_ != nullptr) {
			delete mainWindow_;
			mainWindow_ = nullptr;
		}
		users_.erase(users_.begin(), users_.end());
	}
	dbcontroller_.logUsers();
}

void Controller::processRegistrationRespond(String& message)
{
	String result = wordExtractor_(message);
	dbcontroller_.log(message);
	std::cout << message << std::endl;
	if (result == error) {
		popError_->setText(message);
		popError_->execute();
	} else {
		if (loginWindow_ != nullptr) {
			//loginWindow_->closeRegWindow();
		}
	}
}


void Controller::processUserChangedRespond(String& userStr)
{
	User u;
	String log = "UserChangedRespond: User: \n";
	UserIter it;
	if (!u.fromString(userStr)) {
		log += ". missing from the list.";
		throw Error("Error occurred when processing user changed respond");
	} else {
		it = find(u);
		if (it == users_.end()) {
			users_.push_back(u);
			it = users_.end();
			--it;
			log += ". adding into the list.";
		}
		else {
			it->setStatus(u.getStatus());
			log += ". setting status to " + std::to_string(u.getStatus());
		}
	}
	std::cout << log << std::endl;
	dbcontroller_.log(log);
	dbcontroller_.logUsers();
	updateMainWindow(it);
}

void Controller::processUserListRespond(String& userList)
{
	User u;
	String log = "processUserListResp..." + userList;
	dbcontroller_.log(log);
	std::cout << log << std::endl;
	users_.erase(users_.begin(), users_.end());
	while (u.fromString(userList)) {
		users_.push_back(u);
		log = " adding into the list of users_: " + u.toStringLog();
		dbcontroller_.log(log);
	}
	dbcontroller_.logUsers();
	updateMainWindow();
}

void Controller::processConvRespond(String& msg)
{
	String u = wordExtractor_(msg);
	auto it = find(u);
	if (it == users_.end()) {
		String msg("No user with login-" + u);
		throw Error(msg);
	}
	it->addMessage(msg);
	updateMainWindow(it);
}

Controller::UserIter Controller::find(const String& login)
{
	auto it = users_.begin();
	for (; it != users_.end(); ++it) {
		if (((it->getLogin())) == login) {
			return it;
		}
	}
	return it;
}

Controller::UserIter Controller::find(Controller::User& u)
{
	auto it = users_.begin();
	for (; it != users_.end(); ++it) {
		if ((*(it->getLogin())) == (*(u.getLogin())))
			return it;
	}
	return it;
}


void Controller::updateMainWindow(const UserIter&)
{
	//std::cout << "Controller::updateMainWindow(it)\n";
	mainWindow_->updateMainWindow(users_);
}


void Controller::updateMainWindow()
{
	//std::cout << "Controller::updateMainWindow()\n";
	mainWindow_->updateMainWindow(users_);
}



void* readMessage(void *thisV) {
    Controller::InputReader *thisI = (Controller::InputReader *)thisV;
    thisI->readMessage();
	return nullptr;
}

void* handleSession(void *p)
{
	Controller* ptr = static_cast<Controller*>(p);
	ptr->handleSession();
	return nullptr;
}
