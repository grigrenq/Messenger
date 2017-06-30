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


class Server
{
public:
	using User = ServerUser;
	using UserPtr = boost::shared_ptr<User>;
	using Users = std::vector<UserPtr>;
	using UserIter = Users::iterator;
	using String = std::string;

	using Socket = ip::tcp::socket;
	using SocketPtr = boost::shared_ptr<ip::tcp::socket>;
	using errorCode =  boost::system::error_code;

    Server();

    void run();
    void handleSession(const SocketPtr&);

private:
    void createSocket();
    void setupAddress();
    void bindSocket();
	void listenSocket();
    void acceptClient();
    void doAcceptClient();
	void initializeUsers();

	UserIter find(const SocketPtr&);
	UserIter find(const String&);

	void sendPendingMessages(UserIter);

	bool setOnline(UserIter&);
	bool setOnline(const SocketPtr&);
	bool setOffline(UserIter&);
	bool setOffline(const SocketPtr&);

    void closeSocket(const SocketPtr&);
    int recvMessage(const SocketPtr&, TransportLayer&);
    int sendMessage(const SocketPtr&, String&, const String&);

	void sendUserChangedRespond(const User&);
	void sendConvRespond(const SocketPtr&, const String&, const String&);

	void processMessage(const SocketPtr&, String&);
	void processPlainMessage(String&);
	void processLoginRequest(const SocketPtr&, String&);
	void processLogoutRequest(const SocketPtr&);
	void processRegistrationRequest(const SocketPtr&, String&);
	void processUserListRequest(const SocketPtr&);
	void processPendingMessagesRequest(const SocketPtr&);
	void processConvRequest(const SocketPtr&, String&);

	void handleAccept(const errorCode&, const SocketPtr&);

	Users users_;

	SocketPtr socket_;
    struct sockaddr_in server_;

    bool stopRequested_;
	
	WordExtractor wordExtractor_;
	DBController<Users> dbcontroller_;

	io_service io_service_;
	ip::tcp::acceptor acceptor_;
};

#endif
