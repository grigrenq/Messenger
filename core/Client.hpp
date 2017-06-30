/** 
*  @file    Client.hpp
*  @author  GRI Team
*  @date    06/15/2017  
*  @version 1.0
*  @brief ....
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Includes.hpp"
#include "DBController.hpp"
#include "TransportLayer.hpp"

#include <boost/asio.hpp>
//#include <boost/asio/impl/src.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;


/**
*  @brief Class Client ....  
*/  
class Client
{
public:
	using String = std::string;
	using Socket = ip::tcp::socket;
	using SocketPtr = boost::shared_ptr<ip::tcp::socket>;
	using errorCode = boost::system::error_code;
                
                /** 
                *   @brief Client constructor for class Client
                *   @param  No parametrs  
                */
	Client();
                
                /** 
                *   @brief setupAndConnect calling function createSocket,
setupAddress and connectServer
                *   @param no parametrs 
                *   @return void
                */
		
    void connectServer();
                /** 
                *   @brief closeConnection closing socket that comunicated with server?
                *   @param no parametrs 
                *   @return void
                */
	void closeConnection();
                
                /** 
                *   @brief sendMessage controling process of sending message if
not errors, else asking about errore??
                *   @param Message is an initialized string variable 
                *   @return Integer
                */
	int sendMessage(const String&);
                
                /** 
                *   @brief  recvMessage controling process of receiveing message
if not errors,else asking about errore??   
                *   @param Message is an initialized string variable 
                *   @return Integer
                */  
	int recvMessage(TransportLayer&);

private:

	void handleConnect(const errorCode&);

	SocketPtr socket_;
	io_service io_service_;

	String host_;
	String login_;
};

#endif
