#ifndef CLIENTUSER_HPP
#define CLIENTUSER_HPP

extern const std::string online;
extern const std::string offline;


#include <string>

#include "ExtractWord.hpp"

class ClientUser
{
	public:
		using String = std::string;
		using Messages = std::list<String>;

		ClientUser() 
			: status(false), unreadMessages(0)
		{

		}
		explicit ClientUser(String& clientStr)
			: unreadMessages(0)
		{
			fromString(clientStr);
		}

		bool fromString(String& clientStr)
		{
			//String clientStr(clientStr_);
			login = extractWord(clientStr);
			name = extractWord(clientStr);
			surname = extractWord(clientStr);
			String st = extractWord(clientStr);

			if (login.empty() || name.empty() 
					|| surname.empty() || st.empty()) {
				//throw std::logic_error("Failed converting String to ClientUser.");
				return false;
			}

			if (st == online) {
				status = true;
			} else {
				status = false;
			}
			return true;
		}

		void addMessage(const String& message)
		{
			messages.push_back(message);
			++unreadMessages;
		}

		String toString() {
			String clientStr = login + delim + name + delim + surname + delim;
			if (status == true)
				clientStr = clientStr + online + delim;
			else
				clientStr = clientStr + offline + delim;

			return clientStr;
		}

		

		String getLogin() const { return login; }
		String getName() const { return name; }
		String getSurname() const { return surname; }
		bool getStatus() const { return status; }
		size_t getUnreadMessagesCount() const { return unreadMessages; }
		Messages& getMessages() { return messages; }

		void setStatus(const bool st) { status = st; }
		void setUnreadMessages(const size_t um) { unreadMessages = um; }

		ClientUser* getPointer() { return this; }
	private:
		void operator=(const ClientUser&);
		bool operator==(ClientUser &rhs);

		String login;
		String name;
		String surname;
		bool status;
		size_t unreadMessages;
		Messages messages;

		ExtractWord extractWord;
};//client



#endif
