#include "Controller.hpp"

#include "../gui/LoginWindow.hpp"
#include "../gui/MainWindow/MainWindow.hpp"

#include "MessageTypes.hpp"

Controller::Controller(Client& c_)
	: c(c_)
	, loginWindow(nullptr)
	, mainWindow(nullptr)
	//, dbcontroller(&users)
{
	//
}

void Controller::run()
{
	c.connectServer();
	mainWindow = new MainWindow(*this);
	loginWindow = new LoginWindow(*this);
	loginWindow->showWindow();

	std::shared_ptr<pthread_t> th(new pthread_t);
	if (pthread_create(&(*th), NULL, ::handleContrSession, this)) {
		std::cout << "An error occurred during thread creation process.";
		return;
	}
	//handleSession();
}

String Controller::getLogin() const
{
	return userLogin;
}

void Controller::closeConnection()
{
	c.closeConnection();
}

void Controller::handleSession()
{
	inReaderPtr.reset(new InputReader(*this));
	inReaderPtr->startRead();
	String message;
	while (c.recvMessage(message) == SUCCESS) {
			processMessage(message);
	}
	inReaderPtr->stopRead();
	c.closeConnection();
}

String Controller::sendLoginRequest(const String& login, const String& password)
{
	userLogin = login;
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
	return "Registration request: " + sendMessage(msg, registrationRequest);
}

String Controller::sendMessageToUser(const String& toUser, String& msg)
{
	if (msg.size() == 0) {
		return emptyMessage;
	}
	auto it = find(toUser);
	if (it == users.end()) {
		throw std::logic_error("Attempting to send a message to an unknown user.");
	}
	msg = toUser + delim + msg;
	msg = userLogin + delim + msg;
	return "Message to Client " + toUser + ": " + sendMessage(msg, plainMessage);
}


String Controller::sendConvRequest(const String& uLogin)
{
	String msg = userLogin + delim + uLogin + delim + "Conversation Request";
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
	//usleep(50);
	message = msgType + delim + message;
	if (c.sendMessage(message) == SUCCESS) {
		return success + "message to Server sent.";
	}
	else {
		return error + " occurred when sending message to Server.\n";
	}
}

void Controller::processMessage(String& message)
{
	//dbcontroller.logClient(message);
	//
	String msgType = extractWord(message);
	//std::cout << "Message Type: " << msgType << std::endl;
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
		std::cout << "Unknown type: " << msgType << " message: " << message << std::endl;
	}
}

void Controller::processPlainMessage(String& message)
{
	String fromUser = extractWord(message);
	String log = "From User: " + fromUser + ". message: " + message;
	std::cout << log << std::endl;
	//dbcontroller.logClient(log);

	auto it = find(fromUser);
	if (it == users.end()) {
		throw std::logic_error("The message is from unknown user");
	} else {
		it->addMessage(message);
		updateMessageWindow(it);
	}
}

void Controller::processLoginRespond(String& message)
{
	//dbcontroller.logClient(message);
	String result = extractWord(message);
	if (result == error) {
		//invoke some function of LoginWindow
		std::cout << error << "-" << message << std::endl;
	} else {
		//invoke some function of LoginWindow
		std::cout << success << "-" << message << std::endl;
		sendUserListRequest();
		mainWindow->showWindow();
		if (loginWindow != nullptr) {
			delete loginWindow;
			loginWindow = nullptr;
		//	loginWindow->showWindow();
		}
		//usleep(100);
		//sendPendingMessagesRequest();
		sendConvRequest("222");
	}
	std::cout << message << std::endl;
}

void Controller::processLogoutRespond(String& message)
{
	//dbcontroller.logClient(message);
	String result = extractWord(message);
	String log;
	if (result == error) {
		//invoke some function of Gui
		log =  error + "-" + message;
	} else {
		//invoke some function of Gui
		log = success + "-" + message;
		users.erase(users.begin(), users.end());
	}
	std::cout << log << std::endl;
	//dbcontroller.logClient(log);
	//dbcontroller.logUsers();
}

void Controller::processRegistrationRespond(String& message)
{
	//dbcontroller.logClient(message);
	String result = extractWord(message);
	String log;
	if (result == error) {
		//invoke some function of RegistrationWindow
		log =  error + "-" + message;
	} else {
		//invoke some function of RegistrationWindow
		log = success + "-" + message;
		if (loginWindow != nullptr) {
			//loginWindow->closeRegWindow();
		}
	}
	//dbcontroller.logClient(log);
}


void Controller::processUserChangedRespond(String& userStr)
{
	User u;
	String log = "UserChangedRespond: User: " + u.toString();
	UserIter it;
	if (!u.fromString(userStr)) {
		log += ". missing from the list.";
		//throw std::logic_error("...Error occurred when processing user changed respond");
	} else {
		it = find(u);
		if (it == users.end()) {
			users.push_back(u);
			it = users.end();
			--it;
			log += ". adding into the list.";
		}
		else {
			it->setStatus(u.getStatus());
			log += ". setting status to " + std::to_string(u.getStatus());
		}
	}
	//dbcontroller.logClient(log);
	//dbcontroller.logUsers();
	updateMessageWindow(it);
}

void Controller::processUserListRespond(String& userList)
{
	User u;
	String log = "processUserListResp......";
	//dbcontroller.logClient(log);
	users.erase(users.begin(), users.end());
	while (u.fromString(userList)) {
		users.push_back(u);
		log = " adding into the list of users: " + u.toString();
		//dbcontroller.logClient(log);
	}
	//dbcontroller.logUsers();
	updateMessageWindow(users);
}

void Controller::processConvRespond(String& msg)
{
	//??????????
	//??????????
	String u = extractWord(msg);
	auto it = find(u);
	if (it == users.end()) {
		String msg("No user with login-" + u);
		throw std::logic_error(msg);
	}
	it->addMessage(msg);
	//updateMessageWindow(it);
}

Controller::UserIter Controller::find(const String& login)
{
	auto it = users.begin();
	for (; it != users.end(); ++it) {
		//std::cout << "getLogin() - " << it->getLogin() << ".....login-" << login << std::endl;
		if (it->getLogin() == login) {
			return it;
		}
	}
	return it;
}

Controller::UserIter Controller::find(Controller::User& u)
{
	auto it = users.begin();
	for (; it != users.end(); ++it) {
		if (it->getLogin() == u.getLogin())
			return it;
	}
	return it;
}


void Controller::updateMessageWindow(const UserIter&)
{
	//messageWindow->update(it);
}


void Controller::updateMessageWindow(const Users&)
{
	//messageWindow->update(users_);
}



void* readMessage(void *thisV) {
    Controller::InputReader *thisI = (Controller::InputReader *)thisV;
    thisI->readMessage();
	return nullptr;
}

void* handleContrSession(void *p)
{
	Controller* ptr = static_cast<Controller*>(p);
	ptr->handleSession();
	return nullptr;
}
