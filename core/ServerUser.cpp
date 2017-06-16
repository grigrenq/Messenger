
#include "ServerUser.hpp"


using String = ServerUser::String;

extern const String online;
extern const String offline;

ServerUser::ServerUser()
: sock(INVALID_SOCKET), status(false), pendingMessages(PendigMessages())
{
	//
}

ServerUser::ServerUser(const SOCKET sock_, const String& login_, const String& name_,
		const String& surname_, const String& password_,  const bool st)
: sock(sock_), login(login_), name(name_)
, surname(surname_), password(password_), status(st), pendingMessages(PendigMessages()) 
{
	//
}

ServerUser::ServerUser(const SOCKET sock_)
: sock(sock_), status(false), pendingMessages(PendigMessages())
{
	//
}


String ServerUser::toString() 
{
	String clientStr;
	clientStr = login + delim + name + delim 
		+ surname + delim;
	if (status == true) {
		clientStr += online + delim;
	} else {
		clientStr += offline + delim;
	}
	return clientStr;
}

String ServerUser::toStringLog()
{
	String clientStr = toString();
	clientStr += password + delim;
	clientStr += "Socket = " + std::to_string(sock) + delim;

	return clientStr;
}

bool ServerUser::fromString(String& str)
{
	login = extractWord(str);
	name = extractWord(str);
	surname = extractWord(str);
	password = extractWord(str);

	if (login.empty() || name.empty()
			|| surname.empty() || password.empty()) {
		throw std::logic_error("Failed to convert");
	}
	return true;
}

bool ServerUser::fromString(String& str, int) 
{
	login = extractWord(str);
	password = extractWord(str);
	if (login.empty() ||  password.empty()) {
		throw std::logic_error("Failed to convert");
	}
	return true;
}

SOCKET ServerUser::getSocket() const
{
	return sock; 
}

String ServerUser::getLogin() const 
{
	return login; 
}

String ServerUser::getName() const 
{ 
	return name;
}

String ServerUser::getSurname() const 
{
	return surname; 
}

String ServerUser::getPassword() const 
{
	return password; 
}

bool ServerUser::getStatus() const 
{ 
	return status; 
}

void ServerUser::setSocket(const SOCKET s) const 
{
	sock = s; 
}

void ServerUser::setStatus(const bool st) const 
{
	status = st; 
}

size_t ServerUser::messagesCount() const 
{
	return pendingMessages.size(); 
}

ServerUser::PendigMessages& ServerUser::getPendingMessages() const 
{ 
	return pendingMessages; 
}

void ServerUser::addPendingMessage(const String& msg) const 
{
	pendingMessages.push_back(msg); 
}



void ServerUser::closeSocket() const
{ 
	shutdown(sock,SHUT_RDWR);
	close(sock);
}

bool ServerUser::operator<(const ServerUser& rhs) const 
{
	return (sock < rhs.sock);
}

void ServerUser::operator=(const ServerUser& u)
{
	sock = u.sock;
	login = u.login;
	name = u.name;
	surname = u.surname;
	password = u.password;
	status = u.status;
	pendingMessages = u.pendingMessages;
}

ServerUser* ServerUser::getPointer() const
{ 
	return const_cast<ServerUser*>(this);
}
