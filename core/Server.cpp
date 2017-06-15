#include "Server.hpp"


Server::Server() 
	: socketD(INVALID_SOCKET)
	, stopRequested(false)
	, dbcontroller(&users)
{

}

void Server::run()
{
	createSocket();
	setupAddress();
	bindListen();
	acceptClient();
}

void Server::createSocket() 
{
	socketD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketD == INVALID_SOCKET) {
		String log("Could not create socket - " + std::to_string(socketD));
		dbcontroller.logServer(log);
		std::cout << log << std::endl;
		exit(1);
	}
}

void Server::setupAddress() 
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(DEFAULT_HOST);
	server.sin_port = htons(DEFAULT_PORT);
}

void Server::bindListen() 
{
	int error = bind(socketD, (sockaddr*)&server, sizeof(server));
	if (error < 0) {
		String log("Bind failed with error code - " + std::to_string(error));
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		exit(1);
	}
	listen(socketD, 4);
}

void Server::acceptClient() 
{	
	while (!stopRequested)
		doAcceptClient();
}

void Server::doAcceptClient() 
{
	size_t c = sizeof(sockaddr_in);
	SOCKET sockAccepted = INVALID_SOCKET;
	struct sockaddr_in ServerClient;

	String log("Waiting for incoming connections...\n");
	std::cout << log << std::endl;
	dbcontroller.logServer(log);
	sockAccepted = accept(socketD, (sockaddr*)&ServerClient, (socklen_t*)&c);
	if (sockAccepted == INVALID_SOCKET) {
		log = "Accept failed.";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		return;
	}
	log = "Accepted - " + std::to_string(sockAccepted);
	std::cout << log << std::endl;
	dbcontroller.logServer(log);

	std::pair<Server*, SOCKET> *pairPtr = new std::pair<Server*, SOCKET>(this, sockAccepted);
	std::shared_ptr<pthread_t> shptr(new pthread_t);
	if (pthread_create(&(*shptr), NULL, ::handleServerSession, pairPtr)) {
		log = "An error occurred during thread creation process.";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		return;
	}
	if (threads.find(sockAccepted) == threads.end()) {
		mutGuard mg(mutex);
		threads[sockAccepted] = shptr;
		log = "Thread - " + std::to_string(*(threads.at(sockAccepted))) + " inserted in the map.\n";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
	} else {
		log = "Socket already exists in the map.";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
	}
}


void Server::handleSession(const SOCKET sock)
{
	String msg;
	try {
		while (recvMessage(sock, msg) == SUCCESS) {
			processMessage(sock, msg);
		}
	} catch (const String& e) {
		std::cout << e << std::endl;
	}
	
	closeSocket(sock);
	mutGuard mg(mutex);
	if (threads.find(sock) != threads.end()) {
		pthread_detach(*(threads.at(sock)));
		String log = "Thread - " + std::to_string(*(threads.at(sock))) + " deleted.";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		threads.erase(sock);
	}
}


Server::UserIter Server::find(const SOCKET sock) 
{
	if (sock == INVALID_SOCKET) {
		throw "Cannot find user in the multiset with INVALID_SOCKET";
	}
	mutGuard mg(mutex);
	User u;
	u.setSocket(sock);	
	UserIter it;
	for (it = users.begin(); it != users.end(); ++it) {
		if (it->getSocket() == sock) {
			return it;
		}
	}
	return it;
	//return users.find(u);
}

Server::UserIter Server::find(const String& login)
{	
	mutGuard mg(mutex);
	for (auto it = users.begin(); it != users.end(); ++it) {
		if (it->getLogin() == login) {
			return it;
		}
	}
	return users.end();
}

void Server::sendPendingMessages(const SOCKET sock)
{
	//mutex.lock();
	//mutex.unlock();	//?????????
	auto it = find(sock);
	String log = ".....Attempting to to send pending " + std::to_string(it->messagesCount())
		+ " messages to user: - "	+ it->getLogin() + ".";
	std::cout << log << std::endl;
	dbcontroller.logServer(log);
	if (!it->messagesCount()) {
		log = "....No pending messages for user: " + it->getLogin() + ".";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		return;
	}
	auto messages = it->getPendingMessages();
	while (!messages.empty() && it->getStatus()) {
		sendMessage(sock, messages.front(), plainMessage);
		log = "Sent pending Message: " + messages.front();
		dbcontroller.logServer(log);
		messages.pop_front();
		usleep(300);
	}
}

bool Server::setOnline(UserIter& it)
{
	if (it->getStatus() == false) {
		String log = "Setting online user with login: " + it->getLogin();
		dbcontroller.logServer(log);
		
		mutex.lock();
		auto u = *it;
		users.erase(it);
		u.setStatus(true);
		it = users.insert(u);
		User *p = it->getPointer();	//?????????????
		mutex.unlock();
		dbcontroller.logUsers(); 	//logging
		sendUserChangedRespond(*p);
		return true;
	} else {
		throw std::logic_error("Attempting to set online a user which is already online");
		return false;
	}
}


bool Server::setOffline(UserIter& it)
{	
	if (it->getStatus() == true) {
		mutex.lock();
		String log("Setting Offline user: " + it->getLogin());
		dbcontroller.logServer(log);
		auto u = *it;
		users.erase(it);
		u.setStatus(false);
		u.setSocket(INVALID_SOCKET);
		it = users.insert(u);
		User *p = it->getPointer();	//?????????????
		mutex.unlock();
		dbcontroller.logUsers();	//logging
		sendUserChangedRespond(*p);
		return true;
	} else {
		throw std::logic_error("Attempting to set offline a user which is already offline.");
		return false;
	}
}


void Server::closeSocket(const SOCKET sock)
{
	shutdown(sock,SHUT_RDWR);
	close(sock);
}


int Server::recvMessage(const SOCKET sock, Server::String& msg)
{
	char buffer[DEFAULT_BUFFER];
	int recvSize = recv(sock, buffer, DEFAULT_BUFFER, 0);
	if (recvSize < 0) {
		String log = "Receive failed.Error occurred.";
		std::cout << log << std::endl;
		auto it = find(sock);
		if (it != users.end()) {
			setOffline(it);
			log += "User-" + (it->getLogin()) + " disconnected.";
		} else {
			log += "Unknown socket.";
		}
		dbcontroller.logServer(log);
		closeSocket(sock);
		return ERROR;
	}
	else if (recvSize == SOCKET_CLOSED) {
		String log = "Receive failed. Socket is closed.";
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		auto it = find(sock);
		if (it != users.end()) {
			setOffline(it);
			log += "User-" + (it->getLogin()) + " disconnected.";
		} else {
			log += "Unknown socket.";
		}
		dbcontroller.logClient(log);
		closeSocket(sock);
		return SOCKET_CLOSED;
	}
	else {
		buffer[recvSize] = '\0';
		msg.assign(buffer);
		String log("\n...Row Message: " + msg);
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		return SUCCESS;
	}
}

int Server::sendMessage(const SOCKET sock, String& msg, const String& msgType) 
{
	//usleep(50);

	msg = msgType + delim + msg;
	int sendSize = send(sock, msg.c_str(), msg.size(), 0);
	if (sendSize < 0) {
		String log = "Send failed.Error occurred.";
		auto it = find(sock);
		if (it != users.end()) {
			setOffline(it);
			log += "User-" + (it->getLogin()) + " disconnected.";
		} else {
			log += "Unknown socket.";
		}
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		return ERROR;
	}
	else if (sendSize == SOCKET_CLOSED) {
		closeSocket(sock);
		String log = "Send failed.Socket closed.";
		auto it = find(sock);
		if (it != users.end()) {
			setOffline(it);
			log += "User- " + (it->getLogin()) + " disconnected.";
		} else {
			log += "Unknown socket.";
		}
		std::cout << log << std::endl;
		dbcontroller.logServer(log);
		return SOCKET_CLOSED;
	}
	else {
		String log = "Sent Row Message: " + msg;
		dbcontroller.logServer(log);
		return SUCCESS;
	}
}
void Server::sendUserChangedRespond(User& user)
{
	String userStr = user.toString();
	String log = "sendUserChangedResp......userchanged: " + userStr;
	dbcontroller.logServer(log);
	//mutex.lock();
	for (auto it = users.begin(); it != users.end(); ++it) {
		if (it->getStatus() == true) {
			if (it->getLogin() == user.getLogin()) {
				continue;
			}
			sendMessage(it->getSocket(), userStr, userChangedRespond);
		}
	}
	//mutex.unlock();
}

void Server::sendConvRespond(const SOCKET s, const String& u1, const String& u2)
{
	//??????????????????
}



void Server::processMessage(const SOCKET sock, String& message)
{
	String msgType = extractWord(message);
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
		dbcontroller.logServer(log);
	}
}



void Server::processPlainMessage(String& message)
{
	//mutex.lock();
	/*auto itFrom = find(sock);
	if (itFrom != users.end())
		fromClient = itFrom->getLogin();
	else {
		throw std::logic_error("processPlainMessage: there is no such socket in the multiset.");
		fromClient = "Unknown Client.";
	}*/
	String fromClient = extractWord(message);
	String toClient = extractWord(message);

	message = fromClient + delim + message;
	String log =  "...........attempt to send message: " + message;
	std::cout << log << std::endl;
	dbcontroller.logServer(log);

	auto itToClient = find(toClient);
	if (itToClient != users.end()) {
		//mutex.unlock();
		if (itToClient->getStatus() == true) {
			sendMessage((itToClient->getSocket()), message, plainMessage);
		} else {
			itToClient->addPendingMessage(message);
			log = "pending message - " + message;
			dbcontroller.logServer(log);
		}
	} else {
		//mutex.unlock();
		log + "From-" + extractWord(message) + ". To-" 
			+ toClient + ". Message-" + message;
		dbcontroller.logServer(log);
	}
}


void Server::processLoginRequest(const SOCKET sock, String& message)
{
	User u;
	u.fromString(message, 0);
	String log = "Login request.......(login=" + u.getLogin() + ").(password="
		+ u.getPassword() + ")...." + message;
	dbcontroller.logServer(log);

	String respond;
	//mutex.lock();
	auto it = find(u.getLogin());
	if (it ==  users.end()) {
		respond = error + delim + "Client with login: "	+ u.getLogin() + " is not registered.";
		mutex.unlock();
	} else {
		if (it->getPassword() != u.getPassword()) {
			respond = error + delim + "Wrong password.";
			//mutex.unlock();
		} else {
			if (it->getStatus() == true) {
				respond = error + delim + "Client with login: " + u.getLogin() + " is logged in.";
				//mutex.unlock();
			} else {
				setOnline(it);
				it->setSocket(sock);

				respond = success + delim + "You are logged in.";
				dbcontroller.logUsers();	//logging
				//User *p = it->getPointer();	//????????????
				//mutex.unlock();
			}
		}
	}
	std::cout << "respond = " << respond << std::endl;
	dbcontroller.logServer(respond);
	sendMessage(sock, respond, loginRespond);
}

void Server::processLogoutRequest(const SOCKET sock)
{
	String respond;
	//mutex.lock();
	String test = "processLogoutRequest from socket:" + std::to_string(sock) + "......:";
	std::cout << test << std::endl;
	dbcontroller.logServer(test);
	auto it = find(sock);
	if (it == users.end()) {
		respond = error + delim + "Client with socket:" + std::to_string(sock) + " is not registered.";
	} else {
		if (it->getStatus() == false) {
			respond = error + delim + "Client with login: "	+ it->getLogin() + " is already logged out.";
		} else {
			setOffline(it);

			respond = success + delim + "You are logged out.";
			dbcontroller.logUsers();	//logging
			//User *p = it->getPointer();	//?????????
			//mutex.unlock();
		}
	}
	dbcontroller.logServer(respond);
	sendMessage(sock, respond, logoutRespond);
}

void Server::processRegistrationRequest(const SOCKET sock, String& message)
{

	User u;
	u.fromString(message);
	String log = "Registration request....(login=" + u.getLogin() + ").(name="
		+ u.getName() + ").(surname=" + u.getSurname()
		+ ").(password=" + u.getPassword() + ").(status=" + std::to_string(u.getStatus()) + ")..." + message;
	std::cout << log << std::endl;
	dbcontroller.logServer(log);

	String respond;
	//mutex.lock();
	auto it = find(u.getLogin());
	if (it != users.end()) {
		respond = error + delim + "Client with login: " + u.getLogin() + " is already registered.";
		//mutex.unlock();
	} else {
		it = users.insert(u);
		respond = success + delim + "You are registered.";
		dbcontroller.logUsers();	//logging
		//mutex.unlock();
		User *p = it->getPointer();
		sendUserChangedRespond(*p);
	}
	dbcontroller.logServer(respond);
	sendMessage(sock, respond, registrationRespond);
}

void Server::processUserListRequest(const SOCKET sock)
{
	String respond;
	//mutex.lock();
	for (auto it = users.begin(); it != users.end(); ++it) {
		User *p = it->getPointer();	//???????????????
		respond += p->toString();
	}
	//mutex.unlock();
	if ((respond.size() + userListRespond.size() + 5) < DEFAULT_BUFFER) {
		String log("...Client list request....sent string =" + respond + "....");
		dbcontroller.logServer(log);
		sendMessage(sock, respond, userListRespond);
	}
}

void Server::processPendingMessagesRequest(const SOCKET s)
{
	sendPendingMessages(s);
}

void Server::processConvRequest(const SOCKET s, String& msg)
{
	//????????????????
	
}


void* handleServerSession(void *pairV) 
{
	std::pair<Server*, SOCKET>* p = (std::pair<Server*, SOCKET>*)pairV;
	Server* server = p->first;
	SOCKET sock = p->second;
	server->handleSession(sock);
	return nullptr;
}
