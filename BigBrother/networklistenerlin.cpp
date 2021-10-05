#include "networklistenerlin.h"
#include <iostream>

NetworkListenerLin::NetworkListenerLin(std::shared_ptr<PacketTable> const &table)
    : NetworkListener(table)
{
    sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (sockfd < 0)
    {
        throw std::runtime_error("Socket's initialisation has been failed!");
    }

    std::string devName = "wlp3s0";
    strncpy(ethreq.ifr_name, devName.c_str(), IFNAMSIZ);

    if (ioctl(sockfd, SIOCGIFFLAGS, &ethreq) < 0 )
    {
        throw std::runtime_error("ioctl: get ifflags");
    }

    ethreq.ifr_flags |= IFF_PROMISC;

    if (ioctl(sockfd, SIOCSIFFLAGS, &ethreq) < 0)
    {
        throw std::runtime_error("ioctl: set ifflags");
    }

}

void NetworkListenerLin::ScanNetwork()
{
    std::vector<unsigned char> buffer(maxPacket);

    isRunning.store(true);

    while(isRunning.load())
    {
        recvfrom(sockfd, buffer.data(), maxPacket, 0, NULL, NULL);
    }
}
