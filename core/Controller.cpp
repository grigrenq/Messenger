#include "Controller.hpp"

#include "../gui/LoginWindow.hpp"
#include "../gui/MainWindow/MainWindow.hpp"
#include "../gui/PopError.hpp"

#include "MessageTypes.hpp"
#include "ValidationInfo.hpp"


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

void Controller::run()
{
	c_.connectServer();
	loginWindow_->showLogWindow();
	std::shared_ptr<pthread_t> th(new pthread_t);
	if (pthread_create(&(*th), NULL, ::handleSession, this)) {
		String log("An error occurred during thread creation process.");
		dbcontroller_.log(log);
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
	try {
		while (c_.recvMessage(transportLayer_) == SUCCESS) {
			for (auto p : transportLayer_) {
				processMessage(*p);
			}
			transportLayer_.clear();
		}
	} catch (const Error& err) {
		std::cout << "Error. " << err.what() << std::endl;
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
	return "Registration request: " + sendMessage(msg, registrationRequest);
}

String Controller::sendMessageToUser(const String& toUser, String& msg)
{
	if (msg.empty()) {
		return emptyMessage;
	}
	auto it = find(toUser);
	if (it == users_.end()) {
		throw Error("Attempting to send a message to an unknown user.");
	}
	//std::replace(msg.begin(), msg.end(), '\n', ValidationInfo::newLine);	//boost????
	std::replace(msg.begin(), msg.end(), '\n', '~');
	msg = toUser + delim + msg;
	msg = userLogin_ + delim + msg;
	String res = sendMessage(msg, plainMessage);
	if (res == success) {
		wordExtractor_(msg);
		wordExtractor_(msg);
		wordExtractor_(msg);
		if (wordExtractor_(msg, false) != userLogin_) {
			(*it)->addMessage(msg, false);
		}
	}
	res = "Message to Client " + toUser + ": " + res;
	dbcontroller_.log(res);
	updateMainWindow();
	return res;
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


String Controller::sendMessage(String& msg, const String& msgType)
{
	msg = msgType + delim + msg;
	msg = std::to_string(msg.size()) + delim + msg; 

	if (c_.sendMessage(msg) == SUCCESS) {
		return success;
	} else {
		return error;
	}
}

void Controller::processMessage(String& msg)
{
	dbcontroller_.log(msg);	
	String msgType = wordExtractor_(msg);
	if (msgType == plainMessage) {
		processPlainMessage(msg);
	} else if (msgType == loginRespond) {
		processLoginRespond(msg);
	} else if (msgType == logoutRespond) {
		processLogoutRespond(msg);
	} else if (msgType == registrationRespond) {
		processRegistrationRespond(msg);
	} else if (msgType == userChangedRespond) {
		processUserChangedRespond(msg);
	} else if (msgType == userListRespond) {
		processUserListRespond(msg);
	} else if (msgType == convRespond) {
		processConvRespond(msg);
	} else {
		String log = "Unknown type: " + msgType + " message: " + msg;
		dbcontroller_.log(log);
		throw Error(log);
	}
}

void Controller::processPlainMessage(String& msg)
{
	dbcontroller_.log(msg);
	String fromUser = wordExtractor_(msg, false);
	//std::replace(msg.begin(), msg.end(), ValidationInfo::newLine, String('\n'));	//boost??????
	std::replace(msg.begin(), msg.end(), '~', '\n');
	auto it = find(fromUser);
	if (it == users_.end()) {
		throw Error("The message is from unknown user");
	} else {
		(*it)->addMessage(msg, true);
		updateMainWindow();
	}
}

void Controller::processLoginRespond(String& msg)
{
	dbcontroller_.log(msg);
	String result = wordExtractor_(msg);
	if (result == error) {
		popError_->setText(msg);
		popError_->execute();
		return;
	} else {
		sendUserListRequest();
		if (loginWindow_ != nullptr) {
			loginWindow_->hideLogWindow();
		}
		if (mainWindow_ != nullptr) {
			//std::cout << "mainWindow != nullptr\n";
			mainWindow_->showWindow();
		} else {
			throw Error("Error: MainWindow == nullptr");
		}
		sendPendingMessagesRequest();
	}
}

void Controller::processLogoutRespond(String& msg)
{
	String result = wordExtractor_(msg);
	dbcontroller_.log(msg);
	if (result == error) {
		popError_->setText(msg);
		popError_->execute();
	} else {
		if (mainWindow_ != nullptr) {
			mainWindow_->hide();
			loginWindow_->showLogWindow();
		}
		users_.erase(users_.begin(), users_.end());
	}
	dbcontroller_.logUsers();
}

void Controller::processRegistrationRespond(String& msg)
{
	String result = wordExtractor_(msg);
	dbcontroller_.log(msg);
	if (result == error) {
		return;
		popError_->setText(msg);
		popError_->execute();
	} else {
		closeRegWindow();
	}
}


void Controller::processUserChangedRespond(String& userStr)
{
	UserPtr u(new User());
	String log = "UserChangedRespond: User: ";
	UserIter it;
	if (!(u->fromString(userStr))) {
		log += ". missing from the list.";
		throw Error("Error occurred when processing user changed respond");
	}

	it = find(*u);
	if (it == users_.end()) {
		users_.push_back(u);
		log += ". adding into the list.";
	} else {
		(*it)->setStatus(u->getStatus());
		log += u->getLogin() + ". setting status to " + std::to_string(u->getStatus());
	}
	dbcontroller_.log(log);
	dbcontroller_.logUsers();
	updateMainWindow();
}

void Controller::processUserListRespond(String& userList)
{
	String log = "processUserListResp..." + userList;
	dbcontroller_.log(log);
	users_.erase(users_.begin(), users_.end());
	UserPtr u(new User());
	while (u->fromString(userList)) {
		users_.push_back(u);
		u.reset(new User());
		log = " adding into the list of users_: " + u->toStringLog();
		dbcontroller_.log(log);
	}
	dbcontroller_.logUsers();
	updateMainWindow();
}

void Controller::processConvRespond(String& msg)
{
	dbcontroller_.log(msg);
	String u = wordExtractor_(msg);
	auto it = find(u);
	if (it == users_.end()) {
		String msg("No user with login-" + u);
		throw Error(msg);
	} else {
		std::replace(msg.begin(), msg.end(), '~', '\n');
		(*it)->addMessage(msg, false);
		updateMainWindow();
	}
}

Controller::UserIter Controller::find(const String& login)
{
	auto it = users_.begin();
	for (; it != users_.end(); ++it) {
		if ((*it)->getLogin() == login) {
			return it;
		}
	}
	return it;
}

Controller::UserIter Controller::find(Controller::User& u)
{
	auto it = users_.begin();
	for (; it != users_.end(); ++it) {
		if ((*it)->getLogin() == u.getLogin()) {
			return it;
		}
	}
	return it;
}

void Controller::updateMainWindow()
{
	mainWindow_->updateMainWindow(users_);
}



void* readMessage(void* thisV) {
    Controller::InputReader *thisI = (Controller::InputReader *)thisV;
    thisI->readMessage();
	return nullptr;
}

void* handleSession(void* p)
{
	Controller* ptr = static_cast<Controller*>(p);
	ptr->handleSession();
	return nullptr;
}


void Controller::closeRegWindow()
{
	if (loginWindow_ != nullptr) {
		loginWindow_->closeRegWindow();
	}
}
