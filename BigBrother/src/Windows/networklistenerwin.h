#pragma once
#ifdef __WIN32__

#include <thread>
#include <vector>
#include <array>
#include <winsock2.h>

#define RCVALL 0x98000001

class NetworkListener
{
public:
    NetworkListener();
private:
    SOCKET sock;
    SOCKADDR_IN addr;
    std::string hostName;
};

#endif
