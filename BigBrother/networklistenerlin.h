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
#include "networklistener.h"

class NetworkListenerLin : public NetworkListener
{

public:
    NetworkListenerLin(std::shared_ptr<PacketTable> const &table);
    virtual void ScanNetwork() override;
    ~NetworkListenerLin() { std::cout << "DESTRUCTED!";}

private:
    int sockfd;
    ifreq ethreq;
};

#endif
