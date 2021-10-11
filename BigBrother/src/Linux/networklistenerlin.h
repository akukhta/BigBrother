#ifdef __unix__
#pragma once
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <sys/mman.h>
#include <linux/if.h>
#include <linux/if_packet.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <linux/if_arp.h>
#include <poll.h>
#include <dirent.h>
#include <sys/eventfd.h>
#include "Net/networklistener.h"

//Linux class for network listening
class NetworkListenerLin : public NetworkListener
{

public:
    NetworkListenerLin(std::shared_ptr<PacketTable> const &table, NetworkDevice device, std::function<void (std::vector<unsigned char>)> handlerFunc);
    virtual void ScanNetwork() override;
    static unsigned short int const maxPacket = 65535;
private:
    int sockfd;
    ifreq ethreq;
};

#endif
