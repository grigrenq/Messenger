#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <mutex>
#include <fstream>
#include <string>

#include "ServerUser.hpp"
//#include "ClientUser.hpp"

#include "Conversation.hpp"


class DBController
{
public:
	using ServerUsers = std::multiset<ServerUser>;
	//using ClientUsers = std::list<ClientUser>;
	using String = std::string;
	using mutGuard = std::lock_guard<std::mutex>;
	using Conversations = std::list<Conversation>;
	using ConvIter = Conversations::iterator;

	DBController();
	DBController(ServerUsers*);
	//DBController(ClientUsers*);

	ConvIter findConversation(const String& u1, const String& u2);

	void addMessage(const String& u1, const String& u2, const String& msg);

	void addUser(ServerUser& u);
	void getUsers();

	void logServer(const String& str);
	//void logClient(const String& str);
	void logUsers();

private:
	ServerUsers *serverUsers;
	//ClientUsers *clientUsers;
	std::mutex mutex;
	Conversations conversations;
};

#endif 
