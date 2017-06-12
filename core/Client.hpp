#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Includes.hpp"

class Client
{
	public:
		using String = std::string;

		Client();

		void setupAndConnect();
		void closeConnection();

		int sendMessage(const String&);
		int recvMessage(String&);

	private:
		void createSocket();
		void setupAddress();
		void connectServer();

		SOCKET socketD;
		sockaddr_in server;

		String host;
		String login;
};

#endif
