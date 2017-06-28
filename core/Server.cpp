#include "Server.hpp"
#include "MessageTypes.hpp"
#include <iostream>


Server::Server() 
	: socket_(INVALID_SOCKET)
	, stopRequested_(false)
	, dbcontroller_(&users_)
{

}

void Server::run()
{
	createSocket();
	setupAddress();
	bindSocket();
	listenSocket();
	initializeUsers();
	dbcontroller_.logUsers();
	acceptClient();
}

void Server::createSocket() 
{
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_ == INVALID_SOCKET) {
		String log("Could not create socket - " + std::to_string(socket_));
		dbcontroller_.log(log);
		exit(1);
	}
}

void Server::setupAddress() 
{
	server_.sin_family = AF_INET;
	server_.sin_addr.s_addr = inet_addr(DEFAULT_HOST);
	server_.sin_port = htons(DEFAULT_PORT);
}

void Server::bindSocket() 
{
	int error = bind(socket_, (sockaddr*)&server_, sizeof(server_));
	if (error < 0) {
		String log("Bind failed with error code - " + std::to_string(error));
		dbcontroller_.log(log);
		exit(1);
	}
}
void Server::listenSocket()
{
	listen(socket_, 5);
}


void Server::acceptClient() 
{	
	while (!stopRequested_) {
		doAcceptClient();
		sleep(5);
	}
}

void Server::doAcceptClient() 
{
	size_t c = sizeof(sockaddr_in);
	SOCKET sockAccepted = INVALID_SOCKET;
	struct sockaddr_in ServerClient;

	String log("Waiting for incoming connections...\n");
	dbcontroller_.log(log);
	sockAccepted = accept(socket_, (sockaddr*)&ServerClient, (socklen_t*)&c);
	if (sockAccepted == INVALID_SOCKET) {
		log = "Accept failed.";
		dbcontroller_.log(log);
		return;
	}
	log = "Accepted - " + std::to_string(sockAccepted);
	dbcontroller_.log(log);

	std::pair<Server*, SOCKET> *pairPtr = new std::pair<Server*, SOCKET>(this, sockAccepted);
	std::shared_ptr<pthread_t> shptr(new pthread_t);
	if (pthread_create(&(*shptr), NULL, ::handleSession, pairPtr)) {
		log = "An error occurred during thread creation process.";
		dbcontroller_.log(log);
		return;
	}
	mutGuard mg(mutexThreads_);
	if (threads_.find(sockAccepted) == threads_.end()) {
		threads_[sockAccepted] = shptr;
		log = "Thread - " + std::to_string(*(threads_.at(sockAccepted))) + " inserted in the map.\n";
		dbcontroller_.log(log);
	} else {
		log = "Socket already exists in the map.";
		dbcontroller_.log(log);
	}
}

void Server::initializeUsers()
{
	dbcontroller_.getUsers();
}


void Server::handleSession(const SOCKET& sock)
{
	try {
		TransportLayer tl;
		while (recvMessage(sock, tl) == SUCCESS) {
			for (auto p : tl) {
				processMessage(sock, *p);
			}
			tl.clear();
		}
	} catch (const Error& err) {
		std::cout << err.what() << std::endl;
		closeSocket(socket_);
	}
	
	closeSocket(sock);
	mutGuard mg(mutexThreads_);
	if (threads_.find(sock) != threads_.end()) {
		pthread_detach(*(threads_.at(sock)));
		String log = "Thread - " + std::to_string(*(threads_.at(sock))) + " deleted.";
		std::cout << log << std::endl;
		dbcontroller_.log(log);
		threads_.erase(sock);
	}
}


Server::UserIter Server::find(const SOCKET& sock) 
{
	if (sock == INVALID_SOCKET) {
		String msg("Cannot find user with INVALID_SOCKET ");
		msg += std::to_string(sock);
		dbcontroller_.log(msg);
		throw Error(msg);
	}
	User u;
	u.setSocket(sock);	
	UserIter it = users_.begin();
	for (; it != users_.end(); ++it) {
		if ((*it)->getSocket() == sock) {
			return it;
		}
	}
	return it;
}

Server::UserIter Server::find(const String& login)
{	
	auto it = users_.begin();
	for (; it != users_.end(); ++it) {
		if ((*it)->getLogin() == login) {
			return it;
		}
	}
	return it;
}

void Server::sendPendingMessages(UserIter it)
{
	recMutGuard mg(mutexUsers_);
	(*it)->setPMessages(dbcontroller_.getPMessages((*it)->getLogin()));
	String log("...Attempting to send " + std::to_string((*it)->messagesCount())
			+ " pending messages to user: - "	+ (*it)->getLogin() + ".");
	dbcontroller_.log(log);
	if (!(*it)->messagesCount()) {
		return;
	}
	auto messages = (*it)->getPMessages();
	while (!messages->empty() && (*it)->getStatus()) {
		sendMessage((*it)->getSocket(), messages->front(), plainMessage);
		log = "Sent pending Message: " + messages->front();
		dbcontroller_.log(log);
		messages->pop_front();
	}
	dbcontroller_.addPMsgsToConv((*it)->getLogin());
}

bool Server::setOnline(UserIter& it)
{
	if ((*it)->getStatus() == false) {
		String log = "Setting online user with login: " + (*it)->getLogin();
		dbcontroller_.log(log);
		(*it)->setStatus(true);
		User *p = (*it)->getPointer();
		dbcontroller_.logUsers();
		sendUserChangedRespond(*p);
		return true;
	} else {
		throw Error("Attempting to set online a user which is already online");
	}
	return false;
}

bool Server::setOnline(const SOCKET& sock)
{
	auto it = find(sock);
	if (it == users_.end()) {
		String log("Unknown socket.");
		dbcontroller_.log(log);
		throw Error(log);
	}
	return setOnline(it);
}

bool Server::setOffline(UserIter& it)
{	
	if ((*it)->getStatus() == true) {
		String log("Setting Offline user: " + (*it)->getLogin());
		dbcontroller_.log(log);
		(*it)->setStatus(false);
		(*it)->setSocket(INVALID_SOCKET);
		User *p = (*it)->getPointer();
		dbcontroller_.logUsers();
		sendUserChangedRespond(*p);
		return true;
	} else {
		throw Error("Attempting to set offline a user which is already offline.");
	}
	return false;
}

bool Server::setOffline(const SOCKET& sock)
{
	auto it = find(sock);
	if (it == users_.end()) {
		String log("Unknown socket.");
		dbcontroller_.log(log);
		throw Error(log);
	}
	return setOffline(it);
}


void Server::closeSocket(const SOCKET& sock)
{
	shutdown(sock,SHUT_RDWR);
	close(sock);
}


int Server::recvMessage(const SOCKET& sock, TransportLayer& tl)
{
	int recvSize = recv(sock, tl.getBuffer(), tl.getBufferSize(), 0);
	String log;
	if (recvSize < 0) {
		setOffline(sock);
		log = "Receive failed.Error occurred.";
		log += "User disconnected.";
		dbcontroller_.log(log);
		//closeSocket(sock);
		return ERROR;
	} else if (recvSize == SOCKET_CLOSED) {
		setOffline(sock);
		log = "Receive failed. Socket is closed.";
		log += "User disconnected.";
		dbcontroller_.log(log);
		closeSocket(sock);
		return SOCKET_CLOSED;
	} else {
		tl.setEnd(recvSize);
		tl.processMessage();
		String log("\n...Row Message: ");
		log += tl.getBuffer();
		std::cout << log << std::endl;
		dbcontroller_.log(log);
		return SUCCESS;
	}
}

int Server::sendMessage(const SOCKET& sock, String& msg, const String& msgType) 
{
	msg = msgType + delim + msg;
	msg = std::to_string(msg.size()) + delim + msg;
	std::cout << "function sendMessage-" << msg << std::endl;
	String log;
	int sendSize = send(sock, msg.c_str(), msg.size(), 0);
	if (sendSize < 0) {
		log = "Send failed.Error occurred." + log;
		log += "User disconnected.";	
		std::cout << log << std::endl;
		dbcontroller_.log(log);
		setOffline(sock);
		return ERROR;
	} else if (sendSize == SOCKET_CLOSED) {
		log = "Send failed.Socket closed." + log;
		log += "User disconnected.";
		std::cout << log << std::endl;
		dbcontroller_.log(log);
		setOffline(sock);
		closeSocket(sock);
		return SOCKET_CLOSED;
	} else {
		String log = "Sent Row Message: " + msg;
		dbcontroller_.log(log);
		return SUCCESS;
	}
}

void Server::sendUserChangedRespond(const User& user)
{
	String log = "sendUserChangedResp......userchanged: " + user.toString();
	dbcontroller_.log(log);
	recMutGuard mg(mutexUsers_);
	for (auto it = users_.begin(); it != users_.end(); ++it) {
		if ((*it)->getStatus() == true && (*it)->getLogin() != user.getLogin()) {
			String userStr = user.toString();
			sendMessage((*it)->getSocket(), userStr, userChangedRespond);
		} 
	}
}


void Server::sendConvRespond(const SOCKET& sock, const String& u1, const String& u2)
{
	recMutGuard mg(mutexUsers_);
	auto it = find(sock);
	if (it == users_.end()) {
		String msg("sendConvRespond: could not find user with socket-");
		msg +=  std::to_string(sock);
		dbcontroller_.log(msg);
		throw Error(msg);
	}
	auto c = dbcontroller_.getConversation(u1,u2);
	if (!c) {
		String log("No conversation for user-" + u1 + ", and user-" + u2);
		dbcontroller_.log(log);
		return;
	}
	for (auto it = c->begin(); it != c->end(); ++it) {
		*it = u2 + delim + (*it);
		sendMessage(sock, *it, convRespond);
	}
}



void Server::processMessage(const SOCKET& sock, String& message)
{
	String msgType = wordExtractor_(message);
	if (msgType == plainMessage) {
		processPlainMessage(message);
	} else if (msgType == loginRequest) {
		processLoginRequest(sock, message);
	} else if (msgType == logoutRequest) {
		processLogoutRequest(sock);
	} else if (msgType == registrationRequest) {
		processRegistrationRequest(sock, message);
	} else if (msgType == userListRequest) {
		processUserListRequest(sock);
	} else if (msgType == pendingMessagesRequest) {
		processPendingMessagesRequest(sock);
	} else if (msgType == convRequest) {
		processConvRequest(sock, message);
	} else {
		String log("Unknown type: " + msgType + ". message: " + message);
		std::cout << log << std::endl;
		dbcontroller_.log(log);
	}
}



void Server::processPlainMessage(String& message)
{
	String fromClient = wordExtractor_(message);
	String toClient = wordExtractor_(message);

	message = fromClient + delim + message;
	String log =  "....attempting to send message: " + message;
	dbcontroller_.log(log);

	auto itToClient = find(toClient);
	if (itToClient != users_.end()) {
		if ((*itToClient)->getStatus() == true) {
			dbcontroller_.addMessage(fromClient, toClient, message);
			sendMessage((*itToClient)->getSocket(), message, plainMessage);
		} else {
			dbcontroller_.addPendingMessage(toClient, message);
			log = "pending message - " + message;
			dbcontroller_.log(log);
		}
	} else {
		log + "From-" + wordExtractor_(message) + ". To-" 
			+ toClient + ". Message-" + message;
		dbcontroller_.log(log);
		throw Error(log);
	}
}


void Server::processLoginRequest(const SOCKET& sock, String& message)
{
	User u;
	u.fromString(message, 0);
	String log = "Login request.......(login=" + u.getLogin() + ").(password="
		+ u.getPassword() + ")...." + message;
	dbcontroller_.log(log);

	String respond;
	auto it = find(u.getLogin());
	if (it ==  users_.end()) {
		respond = error + delim + "Client with login: "	+ u.getLogin() + " is not registered.";
		std::cout << respond << std::endl;
	} else {
		if ((*it)->getPassword() != u.getPassword()) {
			respond = error + delim + "Wrong password.";
		} else {
			if ((*it)->getStatus() == true) {
				respond = error + delim + "Client with login: " + u.getLogin() + " is logged in.";
			} else {
				setOnline(it);
				(*it)->setSocket(sock);
				std::cout << "After setting socket-" << (*it)->getSocket() << std::endl;

				respond = success + delim + "You are logged in.";
				dbcontroller_.logUsers();
			}
		}
	}
	dbcontroller_.log(respond);
	sendMessage(sock, respond, loginRespond);
}


void Server::processLogoutRequest(const SOCKET& sock)
{
	String respond;
	String log = "processLogoutRequest from socket:" + std::to_string(sock) + "......:";
	dbcontroller_.log(log);
	auto it = find(sock);
	if (it == users_.end()) {
		respond = error + delim + "Client with socket:" + std::to_string(sock) + " is not registered.";
	} else {
		if ((*it)->getStatus() == false) {
			respond = error + delim + "Client with login: "	+ (*it)->getLogin() + " is already logged out.";
		} else {
			setOffline(it);
			respond = success + delim + "You are logged out.";
			dbcontroller_.logUsers();
		}
	}
	dbcontroller_.log(respond);
	sendMessage(sock, respond, logoutRespond);
}

void Server::processRegistrationRequest(const SOCKET& sock, String& message)
{
	UserPtr u(new User());
	u->fromString(message);
	String log = "Registration request....(login=" + u->getLogin() + ").(name="
		+ u->getName() + ").(surname=" + u->getSurname()
		+ ").(password=" + u->getPassword() + ").(status=" + std::to_string(u->getStatus()) + ")..." + message;
	dbcontroller_.log(log);

	String respond;
	recMutGuard mg(mutexUsers_);
	auto it = find(u->getLogin());
	if (it != users_.end()) {
		respond = error + delim + "Client with login: " + u->getLogin() + " is already registered.";
	} else {
		users_.push_back(u);
		respond = success + delim + "You are registered.";
		dbcontroller_.logUsers();
		User *p = users_.back()->getPointer();
		dbcontroller_.addUser(*p);
		sendUserChangedRespond(*p);
	}
	dbcontroller_.log(respond);
	sendMessage(sock, respond, registrationRespond);
}

void Server::processUserListRequest(const SOCKET& sock)
{
	String respond;
	recMutGuard mg(mutexUsers_);
	for (auto it = users_.begin(); it != users_.end(); ++it) {
		User *p = (*it)->getPointer();
		respond += p->toString();
	}
	if ((respond.size() + userListRespond.size()) < DEFAULT_BUFFER) {
		String log("...Client list request....sent string =" + respond + "....");
		dbcontroller_.log(log);
		sendMessage(sock, respond, userListRespond);
	}
}

void Server::processPendingMessagesRequest(const SOCKET& sock)
{
	auto it = find(sock);
	sendPendingMessages(it);
}

void Server::processConvRequest(const SOCKET& sock, String& msg)
{
	String u1 = wordExtractor_(msg);
	String u2 = wordExtractor_(msg);
	sendConvRespond(sock, u1, u2);
}


void* handleSession(void *pairV) 
{
	std::pair<Server*, SOCKET>* p = (std::pair<Server*, SOCKET>*)pairV;
	Server* server = p->first;
	SOCKET sock = p->second;
	server->handleSession(sock);
	return nullptr;
}
