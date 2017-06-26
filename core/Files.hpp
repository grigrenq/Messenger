#ifndef FILES_HPP
#define FILES_HPP



namespace Files 
{
	using String = std::string;

	const String logDir = "./Log/";
	const String serverUsersDir = "../core/Server/Users/";
	const String convDir = "../core/Server/Conversations/";
	const String pMsgDir = "../core/Server/PendingMessages/";
	const String usersFile = "Users.txt";
	const String convFile = "conversations.txt";
	const String logFile = "log.txt";
	const String fileType = ".txt";
}

#endif
