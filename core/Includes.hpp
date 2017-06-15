#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <cstdlib>

#include <iostream>
#include <string>

#include <cstdio>
#include <unistd.h>

#include <pthread.h>
#include <memory>

#include <set>
#include <map>
#include <list>

#include <mutex>
using mutGuard = std::lock_guard<std::mutex>;

#include <sys/socket.h>
#include "arpa/inet.h"


#define DEFAULT_BUFFER 1024

#define DEFAULT_HOST "192.168.68.148"
//#define LOCAL_HOST "127.0.0.1"
#define DEFAULT_PORT 4857

#ifndef INVALID_SOCKET
const int INVALID_SOCKET = -1;
#endif

#ifndef SOCKET
using SOCKET = int;
#endif

#include <typeinfo>
#include <sstream>

const int ERROR = -1;
const int SUCCESS = 1;
const int SOCKET_CLOSED = 0;

using String = std::string;

const String loginRequest = "loginRequest";
const String loginRespond = "loginRespond";
const String logoutRequest = "logoutRequest";
const String logoutRespond = "logoutRespond";
const String registrationRequest = "regRequest";
const String registrationRespond = "regRespond";
const String pendingMessagesRequest = "pendMsgRequest";
const String userListRequest = "userListRequest";
const String userListRespond = "userListRespond";
const String userChangedRespond = "userChanged";
const String plainMessage = "plainMessage";
const String convRequest = "userConvReq";
const String convRespond = "userConvResp";

const String incorrectLoginOrPassword = "Error. Login or password is incorrect.";
const String incorrectName = "Error. Name or Surname is incorrect.";
const String incorrectPasswords = "Error. Passwords do not match.";
const String emptyMessage = "Error. Message cannot be empty";

const String online = "online";
const String offline = "offline";

const String error = "Error";
const String success = "Success";

const char delim = '%';
const char underscore = '_';

#endif
