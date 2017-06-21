#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <mutex>
#include <fstream>
#include <string>

#include "ServerUser.hpp"
#include "ClientUser.hpp"
#include "Conversation.hpp"
#include "ExtractWord.hpp"


class DBController
{
public:
	using ServerUsers = std::multiset<ServerUser>;
	using ClientUsers = std::list<ClientUser>;
	using String = std::string;
	using mutGuard = std::lock_guard<std::mutex>;
	using Conversations = std::list<Conversation>;
	using ConvIter = Conversations::iterator;
	using ConvPtr = Conversation::ConvPtr;
	using PMessages = ServerUser::PendingMessages;
	using PMessagesPtr = ServerUser::PMessagesPtr;

	DBController();
	DBController(ServerUsers*);
	DBController(ClientUsers*);

	ConvIter findConversation(const String&, const String&);

	void addMessage(const String&, const String&, const String&);
	void addPendingMessage(const String&, const String&);
	void addPMsgsToConv(const String&);

	PMessagesPtr getPMessages(const String&);
	ConvPtr getConversation(const String&, const String&);

	void addUser(ServerUser&);
	void getUsers();

	void logServer(const String&);
	void logClient(const String&);
	void logUsers();

private:
	void clearPMessages(const String&);

	ServerUsers* serverUsers_;
	ClientUsers* clientUsers_;
	std::mutex mutex_;
	Conversations conversations_;
	ExtractWord extractWord_;
};

#endif 
