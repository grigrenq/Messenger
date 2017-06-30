/**
*  @file    ServerUser.hpp
*  @author  GRI Team
*  @date    06/22/2017  
*  @version 1.0 
*  @brief ....
*/

#ifndef SERVERUSER_HPP
#define SERVERUSER_HPP


#include "WordExtractor.hpp"
#include "Includes.hpp"

/**
*  @brief .....  
*/
class ServerUser
{
public:
	using String = std::string;	
	using PMessages = std::list<String>;
	using PMessagesPtr = std::shared_ptr<PMessages>;
	using SizeType = PMessages::size_type;
	using Socket = ip::tcp::socket;

        /** 
        *   @brief ...
        *   @param no parametrs 
        */
        ServerUser();
	
        /** 
        *   @brief.... 
        *   @param  is an initialized....  ??
        */
        ServerUser(const Socket&, const String&, const String&,
			const String&, const String&,  const bool);

        /** 
        *   @brief ....
        *   @param  is an initialized....  ??
        */
        explicit ServerUser(const Socket&);
	

        /** 
        *   @brief ....
        *   @param  no parametrs
        *   @return String
        */
        String toString() const;

        /** 
        *   @brief .....
        *   @param  no parametrs
        *   @return String
        */
        String toStringLog() const;

        /** 
        *   @brief ....
        *   @param  is an initialized....  ??
        *   @return bool
        */
        bool fromString(String&);

        /** 
        *   @brief ....
        *   @param  is an initialized....  ??
        *   @return bool
        */
        bool fromString(String&, int);

        /** 
        *   @brief ...
        *   @param  no parametrs
        *   @return ...
        */
	SOCKET getSocket() const;

        /** 
        *   @brief ....
        *   @param  no parametrs
        *   @return String
        */
        String getLogin() const; 

        /** 
        *   @brief ....
        *   @param  no parametrs
        *   @return String
        */
        String getName() const; 

        /** 
        *   @brief ...
        *   @param  no parametrs
        *   @return String
        */
        String getSurname() const;

        /** 
        *   @brief ...
        *   @param  no parametrs
        *   @return String
        */
        String getPassword() const;

        /** 
        *   @brief ...
        *   @param  no parametrs
        *   @return bool
        */
        bool getStatus() const;

        /** 
        *   @brief ....
        *   @param  is an initialized....  ??
        *   @return void
        */
        void setSocket(const Socket&) const;

        /** 
        *   @brief ....
        *   @param  is an initialized....  ??
        *   @return void
        */
        void setStatus(const bool) const;

        /** 
        *   @brief ...
        *   @param  no parametrs
        *   @return ....
        */
	SizeType messagesCount() const;

        /** 
        *   @brief .....
        *   @param  is an initialized....  ??
        *   @return void
        */
        void setPMessages(PMessagesPtr) const;

        /** 
        *   @brief ......
        *   @param  no parametrs
        *   @return ....
        */
        PMessagesPtr getPMessages() const;

        /** 
        *   @brief ....
        *   @param  no parametrs
        *   @return void
        */
	void closeSocket() const;



        bool operator<(const ServerUser&) const;
	void operator=(const ServerUser&);




        /** 
        *   @brief .....
        *   @param  no parametrs
        *   @return ....
        */
	ServerUser* getPointer() const;

private:
	mutable Socket sock_;
	String login_;
	String name_;
	String surname_;
	String password_;
	mutable bool status_;

	mutable PMessagesPtr pendingMessages_;
	WordExtractor wordExtractor_;
};

#endif
