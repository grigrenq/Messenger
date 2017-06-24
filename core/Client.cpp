#include <iostream>
#include <pthread.h>

#include <sys/socket.h>
#include "arpa/inet.h"


//#include "Includes.hpp"
#include "Client.hpp"



Client::Client()
{
	createSocket();
    setupAddress();
}


void Client::createSocket()
{
	socket_ = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_ == INVALID_SOCKET){
		std::cout << "Could not create socket\n";
		exit(1);
	}
}

void Client::setupAddress()
{
	server_.sin_family = AF_INET;
	server_.sin_addr.s_addr = inet_addr(DEFAULT_HOST);
	server_.sin_port = htons(DEFAULT_PORT);
}

void Client::connectServer()
{
	int error = connect(socket_, (struct sockaddr*)&server_, sizeof(server_));
	if (error < 0)
	{
		std::cout << "Connect Error - " << error << std::endl;
		exit(1);
	}
	std::cout << "Connected\n";
}

int Client::sendMessage(const String& message)
{

	int sendSize = send(socket_, message.c_str(), message.size(), 0);
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
	}
}

int Client::recvMessage(TransportLayer& tl)
{
	int recvSize = recv(socket_, tl.getBuffer(), tl.getBufferSize(), 0);
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
		tl.setEnd(recvSize);
		tl.processMessage();
		return SUCCESS;
	}
}

void Client::closeConnection()
{
	shutdown(socket_, SHUT_RDWR);
	close(socket_);
}
