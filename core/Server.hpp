#ifndef SERVER_HPP
#define SERVER_HPP

#include "Includes.hpp"

#include "ServerUser.hpp"
#include "DBController.hpp"
#include "ExtractWord.hpp"


void* handleSession(void *);

class Server
{
public:
	using User = ServerUser;
	using Users = std::multiset<User>;
	using UserIter = Users::iterator;
	using Threads = std::map<SOCKET, std::shared_ptr<pthread_t>>;
	using String = std::string;

    Server();

    void run(); 
    void handleSession(SOCKET);

private:
    void createSocket();
    void setupAddress();
    void bindListen();
    void acceptClient();
    void doAcceptClient();

	UserIter find(const SOCKET);
	UserIter find(const String&);

	void sendPendingMessages(const SOCKET sock);

	bool setOnline(UserIter&);
	bool setOffline(UserIter&);

    void closeSocket(const SOCKET);
    int recvMessage(const SOCKET, String&);
    int sendMessage(const SOCKET, String& msg, const String& delim);

	void sendUserChangedRespond(User&);

	void processMessage(const SOCKET, String&);
	void processPlainMessage(const SOCKET, String&);
	void processLoginRequest(const SOCKET, String&);
	void processLogoutRequest(const SOCKET);
	void processRegistrationRequest(const SOCKET, String&);
	void processUserListRequest(const SOCKET);

	Users users;

	ExtractWord extractWord;
	DBController dbcontroller;

    SOCKET socketD;
    struct sockaddr_in server;

    Threads threads;
    bool stopRequested;

    std::mutex mutex;
};


#endif

