#ifndef FILES_HPP
#define FILES_HPP


namespace Files 
{
	using String = std::string;

	const String ClientLogDir = "../core/ClientLog/";
	const String ServerLogDir = "../core/ServerLog/";
	const String ServerUsersDir = "../core/Server/Users/";
	const String ConvDir = "../core/Server/Conversations/";
	const String PMsgDir = "../core/Server/PendingMessages/";
	const String logFile = "log.txt";
	const String usersFile = "users.txt";
	const String fileType = ".txt";
}

#endif
