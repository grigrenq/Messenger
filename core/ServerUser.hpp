#ifndef SERVERUSER_HPP
#define SERVERUSER_HPP

#include "ExtractWord.hpp"
#include "Includes.hpp"

class ServerUser
{
public:
	using String = std::string;	
	using PendigMessages = std::list<String>;


	ServerUser();
	ServerUser(const SOCKET, const String&, const String&,
			const String&, const String&,  const bool);
	explicit ServerUser(const SOCKET);
	
	String toString();
	String toStringLog();
	bool fromString(String&);
	bool fromString(String&, int);

	SOCKET getSocket() const;
	String getLogin() const; 
	String getName() const; 
	String getSurname() const;
	String getPassword() const;
	bool getStatus() const;

	void setSocket(const SOCKET) const;
	void setStatus(const bool) const;

	size_t messagesCount() const;
	PendigMessages& getPendingMessages() const;
	void addPendingMessage(const String&) const;

	void closeSocket() const;

	bool operator<(const ServerUser&) const;
	void operator=(const ServerUser&);

	ServerUser* getPointer() const;

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
