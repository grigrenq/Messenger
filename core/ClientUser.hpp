
/** 
*  @file    ClientUser.hpp
*  @author  GRI Team
*  @date    06/21/2017  
*  @version 1.0 
*  @brief ...
*/

#ifndef CLIENTUSER_HPP
#define CLIENTUSER_HPP


#include <string>
#include <list>

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

                /** 
                *   @brief ClientUser is constructor for Class ClientUser   
                */  
		ClientUser();
                /** 
                *   @brief  ...
                *   @param...  
                *   @return ...
                */  
		explicit ClientUser(String&);

		/** 
                *   @brief  ...
                *   @param  ...
                *   @return bool parametr
                */  
                bool fromString(String&);

                /** 
                *   @brief  ...
                *   @param  ...
                *   @return void
                */  
		void addMessage(const String&);

                /** 
                *   @brief  ...
                *   @param  no parametrs 
                *   @return String 
                */  
		String toString();

                /** 
                *   @brief  ...
                *   @param  no parametrs 
                *   @return String
                */  
		String getLogin() const;

                /** 
                *   @brief  ...
                *   @param  no parametrs 
                *   @return String
                */  
		String getName() const;

                /** 
                *   @brief  ....
                *   @param  no parametrs 
                *   @return String
                */  
		String getSurname() const;

                /** 
                *   @brief  ....
                *   @param  no parametrs 
                *   @return bool
                */  
		bool getStatus() const;

                /** 
                *   @brief  ....
                *   @param  no parametrs 
                *   @return ??....
                */  
		SizeType getUnreadMessagesCount() const;

                /** 
                *   @brief  ...
                *   @param  no parametrs
                *   @return ???...
                */  
		Messages& getMessages();

                /** 
                *   @brief  ....
                *   @param  ...
                *   @return void
                */  
		void setStatus(const bool);

                /** 
                *   @brief  ...
                *   @param  ...
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
