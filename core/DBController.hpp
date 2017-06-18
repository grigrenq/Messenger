#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <mutex>
#include <fstream>
#include <string>

#include "ServerUser.hpp"
//#include "ClientUser.hpp"
#include "Conversation.hpp"
#include <memory>
#include "ExtractWord.hpp"


class DBController
{
public:
	using ServerUsers = std::multiset<ServerUser>;
	//using ClientUsers = std::list<ClientUser>;
	using String = std::string;
	using mutGuard = std::lock_guard<std::mutex>;
	using Conversations = std::list<Conversation>;
	using ConvIter = Conversations::iterator;
	using PendingMessages = ServerUser::PendingMessages;
	using PendingMessagesPtr = ServerUser::PendingMessagesPtr;

	DBController();
	DBController(ServerUsers*);
	//DBController(ClientUsers*);

	ConvIter findConversation(const String& u1, const String& u2);

	void addMessage(const String&, const String&, const String& msg);
	void addPendingMessage(const String&, const String&);
	void addPMsgsToConv(const String&);
	PendingMessagesPtr getPMessages(const String&);

	void addUser(ServerUser& u);
	void getUsers();

	void logServer(const String& str);
	//void logClient(const String& str);
	void logUsers();

private:
	void clearPMessages(const String&);

	ServerUsers *serverUsers;
	//ClientUsers *clientUsers;
	std::mutex mutex;
	Conversations conversations;
	ExtractWord extractWord;
};

#endif 
