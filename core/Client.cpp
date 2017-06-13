#include <iostream>
#include <pthread.h>

#include <sys/socket.h>
#include "arpa/inet.h"


//#include "Includes.hpp"
#include "Client.hpp"


Client::Client()
{
	//
}


void Client::createSocket()
{
	socketD = socket(AF_INET, SOCK_STREAM, 0);

	if (socketD == INVALID_SOCKET){
		std::cout << "Could not create socket\n";
		exit(1);
	}
}

void Client::setupAddress()
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(DEFAULT_HOST);
	//server.sin_addr.s_addr = inet_addr(LOCAL_HOST);
	server.sin_port = htons(DEFAULT_PORT);
}

void Client::connectServer()
{
	int error = connect(socketD, (struct sockaddr*)&server, sizeof(server));
	if (error < 0)
	{
		std::cout << "Connect Error - " << error << std::endl;
		exit(1);
	}
	std::cout << "Connected\n";
}

void Client::setupAndConnect()
{
	createSocket();
	setupAddress();
	connectServer();
}

int Client::sendMessage(const String& message)
{
	usleep(100);

	int sendSize = send(socketD, message.c_str(), message.size(), 0);
	if (sendSize < 0) 
	{
		std::cout << "Send failed\n";
		//inReaderPtr->stopRead();
		//closeConnection();
		//exit(1);
		return ERROR;
	}
	else if (sendSize == SOCKET_CLOSED)
	{
		closeConnection();
		//inReaderPtr->stopRead();
		return SOCKET_CLOSED;
	}
	else
	{
		return SUCCESS;
		String log = "Message sent. Row message: " + message;
		std::cout << log << std::endl;
		dbcontroller.logClient(log);
	}
}

int Client::recvMessage(String& message)
{
	char buffer[DEFAULT_BUFFER];
	int recvSize = recv(socketD, buffer, DEFAULT_BUFFER, 0);
	if (recvSize < 0)
	{
		std::cout << "Receive failed\n";
		closeConnection();
		return ERROR;
	}
	else if (recvSize == SOCKET_CLOSED)
	{
		std::cout << "Socket closed.\n";
		closeConnection();
		return SOCKET_CLOSED;
	}
	else
	{
		buffer[recvSize] = '\0';
		message.assign(buffer);

		String log("....Row Message: " + message);
		std::cout << log << std::endl;
		dbcontroller.logClient(log);
		return SUCCESS;
	}
}

void Client::closeConnection()
{
	shutdown(socketD,SHUT_RDWR);
	close(socketD);
}
