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

/**
*  @brief Class Client ....  
*/  
class Client
{
	public:
		using String = std::string;
                
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
		void createSocket();
		void setupAddress();

		SOCKET socket_;
		sockaddr_in server_;

		String host_;
		String login_;
};

#endif
