#include "networklistenerlin.h"
#include <iostream>

NetworkListenerLin::NetworkListenerLin(std::shared_ptr<PacketTable> const &table)
    : NetworkListener(table)
{
    //sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    std::cout << sockfd << std::endl;
    if (sockfd < 0)
    {
        throw std::runtime_error("Socket's initialisation has been failed!");
    }

    gethostname(hostName.data(), hostName.capacity());
    hostent* he =  gethostbyname(hostName.c_str());
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ((in_addr *)he->h_addr_list[0])->s_addr;

    if (bind(sockfd, (sockaddr*) &addr, sizeof(sockaddr)))
    {
        close(sockfd);
        throw std::runtime_error("Socket's binding has been failed!");
    }

    ifreq ethreq;
    std::string deviceName = "wlp3s0";
    strncpy( ethreq.ifr_name, deviceName.c_str(), IFNAMSIZ );

    if (ioctl(sockfd, SIOCGIFFLAGS, &ethreq ) < 0 )
    {
        throw std::runtime_error( "ioctl: get ifflags" );
    }

    ethreq.ifr_flags |= IFF_PROMISC;  // enable 'promiscuous' mode
    if (ioctl( sockfd, SIOCSIFFLAGS, &ethreq ) < 0 )
    {
        throw std::runtime_error( "ioctl: set ifflags" );
    }
}

void NetworkListenerLin::ScanNetwork()
{
    char* data = new char[1536];

    while(true)
    {
        recvfrom(sockfd, data, 1536, 0, NULL, NULL);
        std::cout << std::string(data) << std::endl;
    }
}
