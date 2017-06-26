#ifndef INCLUDES_HPP
#define INCLUDES_HPP
#define DEFAULT_PORT 5921

#include <cstdlib>

#include <iostream>
#include <string>

#include <cstdio>
#include <unistd.h>

#include <pthread.h>
#include <memory>

#include <map>
#include <list>
#include <vector>

#include <mutex>
using mutGuard = std::lock_guard<std::mutex>;
//using mutGuard = std::unique_lock<std::mutex>;

#include <sys/socket.h>
#include "arpa/inet.h"

#define DEFAULT_BUFFER 2048
//#define DEFAULT_HOST "192.168.68.135"
#define DEFAULT_HOST "127.0.0.1"
//#define LOCAL_HOST "127.0.0.1"

using Error = std::logic_error;
using SOCKET = int;
const int INVALID_SOCKET = -1;

const int ERROR = -1;
const int SUCCESS = 1;
const int SOCKET_CLOSED = 0;

#endif
