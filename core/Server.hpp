#ifndef SERVER_HPP
#define SERVER_HPP

#include "Includes.hpp"

#include "ServerUser.hpp"
#include "DBController.hpp"
#include "ExtractWord.hpp"


void* handleServerSession(void *);

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
	void initializeUsers();

	UserIter find(const SOCKET);
	UserIter find(const String&);

	void sendPendingMessages(const SOCKET sock);

	bool setOnline(UserIter&);
	bool setOffline(UserIter&);

    void closeSocket(const SOCKET);
    int recvMessage(const SOCKET, String&);
    int sendMessage(const SOCKET, String&, const String&);

	void sendUserChangedRespond(User&);
	void sendConvRespond(const SOCKET, const String&, const String&);

	void processMessage(const SOCKET, String&);
	void processPlainMessage(String&);
	void processLoginRequest(const SOCKET, String&);
	void processLogoutRequest(const SOCKET);
	void processRegistrationRequest(const SOCKET, String&);
	void processUserListRequest(const SOCKET);
	void processPendingMessagesRequest(const SOCKET);
	void processConvRequest(const SOCKET, String&);

	Users users;

    SOCKET socketD;
    struct sockaddr_in server;

    Threads threads;
    bool stopRequested;

    std::mutex mutex;
	ExtractWord extractWord;
	DBController dbcontroller;
};


#endif

