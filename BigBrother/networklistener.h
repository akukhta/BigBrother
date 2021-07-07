#pragma once
#include "packettable.h"
#define RCVALL 0x98000001
#include <iostream>
class NetworkListener
{
public:

    NetworkListener(std::shared_ptr<PacketTable> const & table) : table(table)
    {
        hostName.reserve(128);
    };

    NetworkListener(NetworkListener const &) = delete;

    virtual void ScanNetwork() = 0;

    virtual ~NetworkListener() = default;

    NetworkListener& operator=(NetworkListener const &) = delete;

protected:
    std::weak_ptr<PacketTable> table;
    std::string hostName;
};
