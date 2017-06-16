#include "ClientUser.hpp"

using String = ClientUser::String;

extern const String online;
extern const String offline;


ClientUser::ClientUser() 
: status(false), unreadMessages(0)
{

}

ClientUser::ClientUser(String& clientStr)
: unreadMessages(0)
{
	fromString(clientStr);
}

bool ClientUser::fromString(String& clientStr)
{
	//String clientStr(clientStr_);
	login = extractWord(clientStr);
	name = extractWord(clientStr);
	surname = extractWord(clientStr);
	String st = extractWord(clientStr);

	if (login.empty() || name.empty() 
			|| surname.empty() || st.empty()) {
		//throw std::logic_error("Failed converting String to ClientUser.");
		return false;
	}

	if (st == online) {
		status = true;
	} else {
		status = false;
	}
	return true;
}

void ClientUser::addMessage(const String& message)
{
	messages.push_back(message);
	++unreadMessages;
}

String ClientUser::toString() {
	String clientStr = login + delim + name + delim + surname + delim;
	if (status == true)
		clientStr = clientStr + online + delim;
	else
		clientStr = clientStr + offline + delim;

	return clientStr;
}



String ClientUser::getLogin() const 
{
	return login; 
}

String ClientUser::getName() const 
{
	return name; 
}

String ClientUser::getSurname() const 
{
	return surname; 
}

bool ClientUser::getStatus() const
{
	return status; 
}

size_t ClientUser::getUnreadMessagesCount() const 
{
	return unreadMessages; 
}

ClientUser::Messages& ClientUser::getMessages() 
{
	return messages; 
}

void ClientUser::setStatus(const bool st) 
{
	status = st; 
}

void ClientUser::setUnreadMessages(const size_t um) 
{ 
	unreadMessages = um;
}

ClientUser* ClientUser::getPointer() 
{
	return this; 
}
