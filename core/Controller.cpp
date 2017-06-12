#include "Controller.hpp"


using String = Controller::String;


Controller::Controller(Client& c_)
	: c(c_) 
	, dbcontroller(&users)
{
	//
}

void Controller::run()
{
	c.setupAndConnect();
	session();
}

void Controller::closeConnection()
{
	c.closeConnection();
}

void Controller::session()
{
	inReaderPtr.reset(new InputReader(*this));
	inReaderPtr->startRead();
	String message;
	while (!inReaderPtr->stopRequested()) {
		if (c.recvMessage(message) == SUCCESS) {
			processMessage(message);
		}
	}
	inReaderPtr->stopRead();
	c.closeConnection();
}

String Controller::sendLoginRequest(const String& login, const String& password)
{
	if (checkLoginPassword(login, password) == false) {
		return incorrectLoginOrPassword;
	}

	String msg = login + delim + password + delim;
	return "Login request: " + sendMessage(msg, loginRequest);
}

String Controller::sendLogoutRequest()
{
	String msg = "This is a logout request.";
	return "Logout request: " + sendMessage(msg, logoutRequest);
}

String Controller::sendRegistrationRequest(const String& login, const String& name,
			const String& surname, const String& password1, const String& password2)
{
	if (checkLoginPassword(login, password1) == false) {
		return incorrectLoginOrPassword;
	}
	if (checkNames(name, surname) == false) {
		return incorrectName;
	}
	if (checkPasswords(password1, password2) == false) {
		return incorrectPasswords;
	}

	String msg = login + delim + name + delim 
			+ surname + delim + password1 + delim;
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
	return "Message to Client " + toUser + ": " + sendMessage(msg, plainMessage);
}

String Controller::sendUserListRequest()
{
	String msg = "This is a user list request.";
	return "Client List request: " + sendMessage(msg, userListRequest);
}

String Controller::sendMessage(String& message, const String& msgType)
{
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
	String msgType = extractWord(message);
	std::cout << "Message Type: " << msgType << std::endl;
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
	} else {
		std::cout << "Unknown type: " << msgType << " message: " << message << std::endl;
	}
}

void Controller::processPlainMessage(String& message)
{
	String fromUser = extractWord(message);
	std::cout << "From User: " << fromUser << ". message: " << message << std::endl;

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
	String result = extractWord(message);
	if (result == error) {
		//invoke some function of LoginWindow
		std::cout << error << "-";
	} else {
		//invoke some function of LoginWindow
		std::cout << success << "-";
		sendUserListRequest();
	}
	std::cout << message << std::endl;
}

void Controller::processLogoutRespond(String& message)
{
	String result = extractWord(message);
	if (result == error) {
		//invoke some function of Gui
		std::cout << error << "-";
	} else {
		//invoke some function of Gui
		std::cout << success << "-";
	}
	std::cout << message << std::endl;
}

void Controller::processRegistrationRespond(String& message)
{
	String result = extractWord(message);
	if (result == error) {
		//invoke some function of RegistrationWindow
		std::cout << error << "-";
	} else {
		//invoke some function of RegistrationWindow
		std::cout << success << "-";
	}
	std::cout << message << std::endl;
}


void Controller::processUserChangedRespond(String& userStr)
{
	User u;
	if (!u.fromString(userStr)) {
		throw std::logic_error("...Error occurred when processing user changed respond");
	}
	auto it = find(u);
	if (it == users.end()) {
		users.push_back(u);
		it = users.end();
		--it;
	}
	else {
		it->setStatus(u.getStatus());
	}

	updateMessageWindow(it);
	dbcontroller.logUsers();
}

void Controller::processUserListRespond(String& userList)
{
	User u;
	users.erase(users.begin(), users.end());
	while (u.fromString(extractUser(userList))) {
		users.push_back(u);
	}
	updateMessageWindow(users);
}


bool Controller::checkLoginPassword(const String& login, const String& password) const
{
	const size_t sz = (login.size() > password.size() ? login.size() : password.size());
	for (auto i = 0; i < sz; ++i) {
		if (i < login.size()) {
			if (!isalnum(login[i])) {
				return false;
			}
		}
		if (i < password.size()) {
			if (!isalnum(password[i])) {
				return false;
			}
		}
	}
	return true;
}


bool Controller::checkNames(const String& name, const String& surname) const
{
	size_t sz = (name.size() > surname.size() ? name.size() : surname.size());
	for (auto i = 0; i < sz; ++i) {
		if (i < name.size()) {
			if (!isalpha(name[i])) {
				return false;
			}
		}
		if (i < surname.size()) {
			if (!isalpha(surname[i])) {
				return false;
			}
		}
	}
	return true;
}

bool Controller::checkPasswords(const String& password1, const String& password2) const
{
	return password1 == password2;
}


String Controller::extractUser(String& userList)
{
	String login = extractWord(userList);
	String name = extractWord(userList);
	String surname = extractWord(userList);
	String status = extractWord(userList);
	return login + delim + name + delim + surname + delim + status + delim;
}

Controller::UserIter Controller::find(const String& login)
{
	auto it = users.begin();
	for (; it != users.end(); ++it) {
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
		if ((*it) == u)
			return it;
	}
	return it;
}


void Controller::updateMessageWindow(const UserIter& it)
{
	//messageWindow->update(it);
}


void Controller::updateMessageWindow(const Users& users_)
{
	//messageWindow->update(users_);
}


void* readMessage(void *thisV) {
    Controller::InputReader *thisI = (Controller::InputReader *)thisV;
    thisI->readMessage();
}
