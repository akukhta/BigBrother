#pragma once
#include <atomic>
#include "Net/networkdevice.h"
#include "Common/packettable.h"
#define RCVALL 0x98000001

//Main class
class NetworkListener
{
public:

    NetworkListener(std::shared_ptr<PacketTable> const & table, NetworkDevice device) : table(table), device(device)
    {
        hostName.reserve(128);
    };

    NetworkListener(NetworkListener const &) = delete;

    virtual void ScanNetwork() = 0;

    virtual ~NetworkListener() = default;

    void StopScan()
    {
        isRunning.store(false);
    }

    NetworkListener& operator=(NetworkListener const &) = delete;

protected:
    std::weak_ptr<PacketTable> table;
    std::string hostName;
    std::atomic_bool isRunning;
    NetworkDevice device;
};
