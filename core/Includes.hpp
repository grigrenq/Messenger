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

#define DEFAULT_HOST "127.0.0.1" //"192.168.68.148"
#define LOCAL_HOST "127.0.0.1"
#define DEFAULT_PORT 4859

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET
#define SOCKET int
#endif

#include <typeinfo>
#include <sstream>

#define ERROR -1
#define SUCCESS 1
#define SOCKET_CLOSED 0


const std::string loginRequest = "loginRequest";
const std::string loginRespond = "loginRespond";

const std::string logoutRequest = "logoutRequest";
const std::string logoutRespond = "logoutRespond";

const std::string registrationRequest = "regRequest";
const std::string registrationRespond = "regRespond";

const std::string userChangedRespond = "userChanged";

const std::string userListRequest = "userListRequest";
const std::string userListRespond = "userListRespond";

const std::string plainMessage = "plainMessage";

const std::string incorrectLoginOrPassword = "Error. Login or password is incorrect.";
const std::string incorrectName = "Error. Name or Surname is incorrect.";
const std::string incorrectPasswords = "Error. Passwords do not match.";
const std::string emptyMessage = "Error. Message cannot be empty";

const std::string online = "online";
const std::string offline = "offline";

const std::string error = "Error";
const std::string success = "Success";

const char delim = '%';

#endif
