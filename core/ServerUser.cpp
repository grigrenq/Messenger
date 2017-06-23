#include "ServerUser.hpp"
#include "MessageTypes.hpp"



ServerUser::ServerUser()
: sock_(INVALID_SOCKET), status_(false)
{
	//
}

ServerUser::ServerUser(const SOCKET sock, const String& login, const String& name,
		const String& surname, const String& password,  const bool st)
: sock_(sock), login_(login), name_(name)
, surname_(surname), password_(password), status_(st)
{
	//
}

ServerUser::ServerUser(const SOCKET sock)
: sock_(sock), status_(false)
{
	//
}


String ServerUser::toString() const
{
	String clientStr;
	clientStr = login_ + delim + name_ + delim 
		+ surname_ + delim;
	if (status_ == true) {
		clientStr += online + delim;
	} else {
		clientStr += offline + delim;
	}
	return clientStr;
}

String ServerUser::toStringLog() const
{
	String clientStr = toString();
	clientStr += password_ + delim;
	clientStr += "Socket = " + std::to_string(sock_) + delim;

	return clientStr;
}

bool ServerUser::fromString(String& str)
{
	login_ = wordExtractor_(str);
	name_ = wordExtractor_(str);
	surname_ = wordExtractor_(str);
	String st = wordExtractor_(str);
	if (st == online) {
		status_ = true;
	} else {
		status_ = false;
	}
	password_ = wordExtractor_(str);

	if (login_.empty() || name_.empty()
			|| surname_.empty() || password_.empty()) {
		throw std::logic_error("fromString(String&)...Failed to convert");
	}
	return true;
}

bool ServerUser::fromString(String& str, int) 
{
	login_ = wordExtractor_(str);
	password_ = wordExtractor_(str);
	if (login_.empty() ||  password_.empty()) {
		throw std::logic_error("Failed to convert");
	}
	return true;
}

SOCKET ServerUser::getSocket() const
{
	return sock_; 
}

String ServerUser::getLogin() const 
{
	return login_; 
}

String ServerUser::getName() const 
{ 
	return name_;
}

String ServerUser::getSurname() const 
{
	return surname_;
}

String ServerUser::getPassword() const 
{
	return password_; 
}

bool ServerUser::getStatus() const 
{ 
	return status_; 
}

void ServerUser::setSocket(const SOCKET s) const 
{
	sock_ = s; 
}

void ServerUser::setStatus(const bool st) const 
{
	status_ = st; 
}

ServerUser::SizeType ServerUser::messagesCount() const 
{
	if (!pendingMessages_) {
		return 0;
	}
	return pendingMessages_->size(); 
}

void ServerUser::setPMessages(PMessagesPtr pm) const
{
	pendingMessages_ = pm;
}



ServerUser::PMessagesPtr ServerUser::getPMessages() const
{ 
	return pendingMessages_; 
}


void ServerUser::closeSocket() const
{ 
	shutdown(sock_,SHUT_RDWR);
	close(sock_);
}

bool ServerUser::operator<(const ServerUser& rhs) const 
{
	return (sock_ < rhs.sock_);
}

void ServerUser::operator=(const ServerUser& u)
{
	sock_ = u.sock_;
	login_ = u.login_;
	name_ = u.name_;
	surname_ = u.surname_;
	password_ = u.password_;
	status_ = u.status_;
	pendingMessages_ = u.pendingMessages_;
}

ServerUser* ServerUser::getPointer() const
{ 
	return const_cast<ServerUser*>(this);
}
