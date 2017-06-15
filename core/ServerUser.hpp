#ifndef SERVERUSER_HPP
#define SERVERUSER_HPP

#include "ExtractWord.hpp"

class ServerUser
{
public:
	using String = std::string;	
	using PendigMessages = std::list<String>;


	ServerUser()
		: sock(INVALID_SOCKET), status(false), pendingMessages(PendigMessages())
	{
		//
	}

	explicit ServerUser(const SOCKET sock_, const String& login_, const std::string& name_,
			const String& surname_, const std::string& password_,  const bool st)
		: sock(sock_), login(login_), name(name_)
		, surname(surname_), password(password_), status(st), pendingMessages(PendigMessages()) 
	{
		//
	}

	explicit ServerUser(const SOCKET sock_)
		: sock(sock_), status(false), pendingMessages(PendigMessages())
	{
		//
	}
	
	String toString() 
	{
		String clientStr;
		clientStr = login + delim + name + delim 
			+ surname + delim;
		if (status == true) {
			clientStr += online + delim;
		} else {
			clientStr += offline + delim;
		}
		return clientStr;
	}
	String toStringLog()
	{
		String clientStr = toString();
		clientStr += password + delim;
		clientStr += "Socket = " + std::to_string(sock) + delim;

		return clientStr;
	}
	bool fromString(String& str)
	{
		login = extractWord(str);
		name = extractWord(str);
		surname = extractWord(str);
		password = extractWord(str);

		if (login.empty() || name.empty()
				|| surname.empty() || password.empty()) {
			throw std::logic_error("Failed to convert");
		}
		return true;
	}
	bool fromString(String& str, int) 
	{
		login = extractWord(str);
		password = extractWord(str);
		if (login.empty() ||  password.empty()) {
			throw std::logic_error("Failed to convert");
		}
		return true;
	}

	SOCKET getSocket() const { return sock; }
	String getLogin() const { return login; }
	String getName() const { return name; }
	String getSurname() const { return surname; }
	String getPassword() const { return password; }
	bool getStatus() const { return status; }

	size_t messagesCount() const { return pendingMessages.size(); }
	PendigMessages& getPendingMessages() const { return pendingMessages; }

	void setSocket(const SOCKET s) const { sock = s; }
	void setStatus(const bool st) const { status = st; }

	void addPendingMessage(const String& msg) const { pendingMessages.push_back(msg); }

	void closeSocket() const
	{ 
		shutdown(sock,SHUT_RDWR);
		close(sock);
	}

	bool operator<(const ServerUser& rhs) const 
	{
		return (sock < rhs.sock);
	}

	ServerUser* getPointer() const
	{ 
		return const_cast<ServerUser*>(this);
	}

	void operator=(const ServerUser& u)
	{
		sock = u.sock;
		login = u.login;
		name = u.name;
		surname = u.surname;
		password = u.password;
		status = u.status;
		pendingMessages = u.pendingMessages;
	}
private:
	mutable SOCKET sock;
	String login;
	String name;
	String surname;
	String password;
	mutable bool status;
	mutable PendigMessages pendingMessages;

	ExtractWord extractWord;
};

#endif
