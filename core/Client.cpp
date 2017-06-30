#include <iostream>
#include <pthread.h>

#include <sys/socket.h>
#include "arpa/inet.h"


#include "Client.hpp"


Client::Client()
{
	socket_.reset(new Socket(io_service_));
	connectServer();
	io_service_.run();
}

void Client::connectServer()
{
	std::cout << "Attempting to connect to server.\n";
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 9758);
	socket_->async_connect(ep, boost::bind(&Client::handleConnect, this, _1));
}

int Client::sendMessage(const String& message)
{
	/*int sendSize = send(socket_, message.c_str(), message.size(), 0);
	if (sendSize < 0) {
		std::cout << "Send failed\n";
		//inReaderPtr->stopRead();
		//closeConnection();
		//exit(1);
		return ERROR;
	} else if (sendSize == SOCKET_CLOSED) {
		closeConnection();
		//inReaderPtr->stopRead();
		return SOCKET_CLOSED;
	} else {
		return SUCCESS;
	}
	*/
	return ERROR;
}

int Client::recvMessage(TransportLayer& tl)
{
	/*int recvSize = recv(socket_, tl.getBuffer(), tl.getBufferSize(), 0);
	if (recvSize < 0) {
		std::cout << "Receive failed\n";
		//closeConnection();
		return ERROR;
	} else if (recvSize == SOCKET_CLOSED) {
		std::cout << "Socket closed.\n";
		closeConnection();
		return SOCKET_CLOSED;
	} else {
		tl.setEnd(recvSize);
		tl.processMessage();
		return SUCCESS;
	}
	*/
	return ERROR;
}

void Client::closeConnection()
{
	errorCode err;
	socket_->shutdown(socket_base::shutdown_both, err);
	socket_->close(err);
}

void Client::handleConnect(const errorCode& err)
{
	if (err) {
		std::cout << "Connect failed. err - " << err << std::endl;
		return;
	}
	std::cout << "Connected.\n";
}
