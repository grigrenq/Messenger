
/** 
*  @file    ClientUser.hpp
*  @author  GRI Team
*  @date    06/21/2017  
*  @version 1.0 
*  @brief 
*/

#ifndef CLIENTUSER_HPP
#define CLIENTUSER_HPP


#include <string>
#include <list>
#include <memory>

#include "ExtractWord.hpp"


/**
*  @brief ClientUser Class  
*/  
class ClientUser
{
	public:
		using String = std::string;
        using SizeType = String::size_type;
		using Messages = std::list<String>;
		using StringPtr = std::shared_ptr<String>;

                /** 
                *   @brief ClientUser is constructor for Class ClientUser   
                */  
		ClientUser();
                /** 
                *   @brief  ClientUser is constructor for Class ClientUser
                *   @param  Reference of String
                */  
		explicit ClientUser(String&);

		/** 
                *   @brief  set parametrs login, name, surname, string and check if this empty
                *   @param  Reference of String
                *   @return bool parametr
                */  
                bool fromString(String&);

                /** 
                *   @brief  addMessage asign new message in old mesages and increase by one
                *   @param  const reference of String??
                *   @return void
                */  
		void addMessage(const String&);

                /** 
                *   @brief toString add login name and surname in string 
                *   @param  no parametrs 
                *   @return String 
                */  
		String toStringLog() const;

                /** 
                *   @brief  getLogin return login
                *   @param  no parametrs 
                *   @return String
                */  
		const char* getLogin() const;

                /** 
                *   @brief  getName return name
                *   @param  no parametrs 
                *   @return String
                */  
		String getName() const;

                /** 
                *   @brief  getSurname return surname
                *   @param  no parametrs 
                *   @return String
                */  
		String getSurname() const;

                /** 
                *   @brief  getStatus return status
                *   @param  no parametrs 
                *   @return bool
                */  
		bool getStatus() const;

                /** 
                *   @brief  getUnreadMessagesCount return unread messages count
                *   @param  no parametrs 
                *   @return SizeType,it's size of string
                */  
		SizeType getUnreadMessagesCount() const;

                /** 
                *   @brief  getMessages return messages
                *   @param  no parametrs
                *   @return ???...
                */  
		Messages& getMessages();

                /** 
                *   @brief  asigne the value to status 
                *   @param  const bool parametr?
                *   @return void
                */  
		void setStatus(const bool);

                /** 
                *   @brief  asign the value to unread messages
                *   @param  size of string
                *   @return void
                */  
		void setUnreadMessages(const SizeType);

                /** 
                *   @brief  ...
                *   @param  no parametrs
                *   @return ...
                */      
                ClientUser* getPointer();
	private:
		void operator=(const ClientUser&);
		bool operator==(const ClientUser&);

		String login_;
		String name_;
		String surname_;
		bool status_;
		size_t unreadMessages_;
		Messages messages_;

		ExtractWord extractWord_;
};

#endif
