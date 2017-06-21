#ifndef CLIENTUSER_HPP
#define CLIENTUSER_HPP


#include <string>
#include <list>

#include "ExtractWord.hpp"

class ClientUser
{
	public:
		using String = std::string;
		using Messages = std::list<String>;

		ClientUser();
		explicit ClientUser(String&);

		bool fromString(String&);

		void addMessage(const String&);

		String toString();

		String getLogin() const;
		String getName() const;
		String getSurname() const;
		bool getStatus() const;
		size_t getUnreadMessagesCount() const;
		Messages& getMessages();

		void setStatus(const bool);
		void setUnreadMessages(const size_t);

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
