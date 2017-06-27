#ifndef SERVER_HPP
#define SERVER_HPP

#include "Includes.hpp"

#include "ServerUser.hpp"
#include "DBController.hpp"
#include "WordExtractor.hpp"
#include "TransportLayer.hpp"


void* handleSession(void *);

class Server
{
public:
	using User = ServerUser;
	using UserPtr = std::shared_ptr<User>;
	using Users = std::vector<UserPtr>;
	using UserIter = Users::iterator;
	using Threads = std::map<SOCKET, std::shared_ptr<pthread_t>>;
	using String = std::string;

    Server();

    void run();
    void handleSession(SOCKET);

private:
    void createSocket();
    void setupAddress();
    void bindSocket();
	void listenSocket();
    void acceptClient();
    void doAcceptClient();
	void initializeUsers();

	UserIter find(const SOCKET);
	UserIter find(const String&);

	void sendPendingMessages(UserIter);

	bool setOnline(UserIter&);
	bool setOffline(UserIter&);

    void closeSocket(const SOCKET);
    int recvMessage(const SOCKET, TransportLayer&);
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

	Users users_;

    SOCKET socket_;
    struct sockaddr_in server_;

    Threads threads_;
    bool stopRequested_;
	
	std::mutex mutexThreads_;
    std::recursive_mutex mutex_;
	WordExtractor wordExtractor_;
	DBController<Users> dbcontroller_;
};


#endif

