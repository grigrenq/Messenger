#ifndef SERVER_HPP
#define SERVER_HPP

#include "Includes.hpp"

#include "ServerUser.hpp"
#include "DBController.hpp"
#include "WordExtractor.hpp"
#include "TransportLayer.hpp"


#include <boost/asio.hpp>
//#include <boost/asio/impl/src.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


using namespace boost::asio;
using SocketPtr boost::shared_ptr<ip::tcp::socket>;
using errorCode  boost::system::error_code;


class Server
{
public:
	using User = ServerUser;
	using UserPtr = std::shared_ptr<User>;
	using Users = std::vector<UserPtr>;
	using UserIter = Users::iterator;
	using String = std::string;

	using Socket = ip::tcp::socket;
	using Threads = std::map<SocketPtr, boost::thread>;

    Server();

    void run();
    void handleSession(const Socket&);

private:
    void createSocket();
    void setupAddress();
    void bindSocket();
	void listenSocket();
    void acceptClient();
    void doAcceptClient();
	void initializeUsers();

	UserIter find(const Socket&);
	UserIter find(const String&);

	void sendPendingMessages(UserIter);

	bool setOnline(UserIter&);
	bool setOnline(const Socket&);
	bool setOffline(UserIter&);
	bool setOffline(const Socket&);

    void closeSocket(const Socket&);
    int recvMessage(const Socket&, TransportLayer&);
    int sendMessage(const Socket&, String&, const String&);

	void sendUserChangedRespond(const User&);
	void sendConvRespond(const Socket&, const String&, const String&);

	void processMessage(const Socket&, String&);
	void processPlainMessage(String&);
	void processLoginRequest(const Socket&, String&);
	void processLogoutRequest(const Sokcet&);
	void processRegistrationRequest(const Socket&, String&);
	void processUserListRequest(const Socket&);
	void processPendingMessagesRequest(const Socket&);
	void processConvRequest(const Socket&, String&);

	Users users_;

	Socket socket_;
    struct sockaddr_in server_;

    Threads threads_;
    bool stopRequested_;
	
	std::mutex mutexThreads_;
    std::recursive_mutex mutexUsers_;
	WordExtractor wordExtractor_;
	DBController<Users> dbcontroller_;

	io_service io_service_;
	ip::tcp::acceptor acceptor_;
};

#endif
