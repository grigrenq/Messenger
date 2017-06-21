#include "ClientUser.hpp"
#include "MessageTypes.hpp"

using String = ClientUser::String;

//extern const String online;
//extern const String offline;
//extern const char delim;


ClientUser::ClientUser() 
: status_(false), unreadMessages_(0)
{

}

ClientUser::ClientUser(String& clientStr)
: unreadMessages_(0)
{
	fromString(clientStr);
}

bool ClientUser::fromString(String& clientStr)
{
	login_ = extractWord_(clientStr);
	name_ = extractWord_(clientStr);
	surname_ = extractWord_(clientStr);
	String st = extractWord_(clientStr);

	if (login_.empty() || name_.empty() 
			|| surname_.empty() || st.empty()) {
		return false;
	}

	if (st == online) {
		status_ = true;
	} else {
		status_ = false;
	}
	return true;
}

void ClientUser::addMessage(const String& message)
{
	messages_.push_back(message);
	++unreadMessages_;
}

String ClientUser::toString() {
	String clientStr = login_ + delim + name_ + delim + surname_ + delim;
	if (status_ == true)
		clientStr = clientStr + online + delim;
	else
		clientStr = clientStr + offline + delim;

	return clientStr;
}



String ClientUser::getLogin() const 
{
	return login_; 
}

String ClientUser::getName() const 
{
	return name_; 
}

String ClientUser::getSurname() const 
{
	return surname_; 
}

bool ClientUser::getStatus() const
{
	return status_; 
}

ClientUser::SizeType ClientUser::getUnreadMessagesCount() const 
{
	return unreadMessages_; 
}

ClientUser::Messages& ClientUser::getMessages() 
{
	return messages_; 
}

void ClientUser::setStatus(const bool st) 
{
	status_ = st; 
}

void ClientUser::setUnreadMessages(const SizeType um) 
{ 
	unreadMessages_ = um;
}

ClientUser* ClientUser::getPointer() 
{
	return this; 
}
