#ifndef SERVERUSER_HPP
#define SERVERUSER_HPP

#include "ExtractWord.hpp"
#include "Includes.hpp"


class ServerUser
{
public:
	using String = std::string;	
	using PendingMessages = std::list<String>;
	using SizeType = PendingMessages::size_type;
	using PMessagesPtr = std::shared_ptr<PendingMessages>;


	ServerUser();
	ServerUser(const SOCKET, const String&, const String&,
			const String&, const String&,  const bool);
	explicit ServerUser(const SOCKET);
	
	String toString() const;
	String toStringLog() const;
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

	SizeType messagesCount() const;
	void setPMessages(PMessagesPtr) const;
	PMessagesPtr getPMessages() const;

	void closeSocket() const;

	bool operator<(const ServerUser&) const;
	void operator=(const ServerUser&);

	ServerUser* getPointer() const;

private:
	mutable SOCKET sock_;
	String login_;
	String name_;
	String surname_;
	String password_;
	mutable bool status_;

	mutable PMessagesPtr pendingMessages_;
	ExtractWord extractWord_;
};

#endif
