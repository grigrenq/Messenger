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
//#define DEFAULT_HOST "192.168.68.148"
#define DEFAULT_HOST "127.0.0.1"
//#define LOCAL_HOST "127.0.0.1"
#define DEFAULT_PORT 4855


using SOCKET = int;
const int INVALID_SOCKET = -1;

const int ERROR = -1;
const int SUCCESS = 1;
const int SOCKET_CLOSED = 0;

using Error = std::logic_error;

#endif
