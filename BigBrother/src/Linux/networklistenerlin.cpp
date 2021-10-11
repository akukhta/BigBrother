#include "networklistenerlin.h"
#include <iostream>
#include <thread>

NetworkListenerLin::NetworkListenerLin(std::shared_ptr<PacketTable> const &table, NetworkDevice device, std::function<void (std::vector<unsigned char>)> handlerFunc)
    : NetworkListener(table, device, handlerFunc)
{
    sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (sockfd < 0)
    {
        throw std::runtime_error("Socket's initialisation has been failed!");
    }

    strncpy(ethreq.ifr_name, device.name.c_str(), IFNAMSIZ);

    if (ioctl(sockfd, SIOCGIFFLAGS, &ethreq) < 0 )
    {
        throw std::runtime_error("ioctl: get ifflags");
    }

    ethreq.ifr_flags |= IFF_PROMISC;

    if (ioctl(sockfd, SIOCSIFFLAGS, &ethreq) < 0)
    {
        throw std::runtime_error("ioctl: set ifflags");
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, &ethreq, sizeof(ethreq)) < 0)
    {
        throw std::runtime_error("setsockopt: can`t bind socket to specific device");
    }

}

void NetworkListenerLin::ScanNetwork()
{   
    std::vector<unsigned char> buffer(NetworkListenerLin::maxPacket);
    ssize_t received;

    isRunning.store(true);

    struct sockaddr saddr;
    int saddr_len = sizeof (saddr);

    while(isRunning.load())
    {
        received = recvfrom(sockfd, buffer.data(), NetworkListenerLin::maxPacket, 0, NULL, NULL);
        if (received > 0)
        {
            std::cout << std::this_thread::get_id() << "is running" << std::endl;
            handlerFunc(std::move(std::vector<unsigned char>(buffer.begin(), buffer.begin() + received)));
        }
    }
}
