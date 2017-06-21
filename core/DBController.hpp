#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <mutex>
#include <fstream>
#include <string>

#include "ServerUser.hpp"
#include "ClientUser.hpp"
#include "Conversation.hpp"
#include "ExtractWord.hpp"


template<typename Users>
class DBController
{
public:
	using User = typename Users::value_type;
	using String = std::string;
	using mutGuard = std::lock_guard<std::mutex>;
	using Conversations = std::list<Conversation>;
	using ConvIter = Conversations::iterator;
	using ConvPtr = Conversation::ConvPtr;
	using PMessages = ServerUser::PendingMessages;
	using PMessagesPtr = ServerUser::PMessagesPtr;

	DBController();
	DBController(Users*);

	ConvIter findConversation(const String&, const String&);

	void addMessage(const String&, const String&, const String&);
	void addPendingMessage(const String&, const String&);
	void addPMsgsToConv(const String&);

	PMessagesPtr getPMessages(const String&);
	ConvPtr getConversation(const String&, const String&);

	void addUser(const User&);
	void getUsers();

	void log(const String&);
	void logUsers();

private:
	void clearPMessages(const String&);
	void setupFiles();

	Users* users_;
	std::mutex mutex_;
	Conversations conversations_;
	ExtractWord extractWord_;

	String logFile_;
	String usersLogFile_;
};

#include "DBController.icpp"

#endif


