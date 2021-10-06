#include "networklistenerlin.h"
#include <iostream>
#include <thread>

NetworkListenerLin::NetworkListenerLin(std::shared_ptr<PacketTable> const &table, NetworkDevice device)
    : NetworkListener(table, device)
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

}

void NetworkListenerLin::ScanNetwork()
{   
    std::vector<unsigned char> buffer(device.MTU);

    isRunning.store(true);

    while(isRunning.load())
    {
        recvfrom(sockfd, buffer.data(), maxPacket, 0, NULL, NULL);
        std::cout << std::this_thread::get_id() << "is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

    }
}
