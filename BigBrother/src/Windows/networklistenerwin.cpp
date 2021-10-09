#include "networklistener.h"
#ifdef __WIN32__

NetworkListener::NetworkListener()
{
    WSADATA wsData;
    WORD dllVersion = MAKEWORD(2,2);
    bool wsaInitErr = WSAStartup(dllVersion, &wsData);

    if(wsaInitErr)
    {
       throw std::runtime_error("Socket's library's init has been failed");
    }

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);

    if (sock == INVALID_SOCKET)
    {
        throw std::runtime_error("Socket's init has been failed with WSAGetLasError = " + std::to_string(WSAGetLastError()));
    }

    hostName.reserve(128);
    gethostname(hostName.data(), hostName.length());
    HOSTENT *he = gethostbyname(hostName.c_str());

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ((struct in_addr *)he->h_addr_list[0])->s_addr;

    bind(sock, (SOCKADDR *) &addr, sizeof(SOCKADDR));
    unsigned long flag = 1;

    if (ioctlsocket(sock, RCVALL, &flag) != 0)
    {
        throw std::runtime_error("Socket's configuration has been failed");
    }

}

#endif
