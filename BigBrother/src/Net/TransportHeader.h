#pragma once
#include "Common/packethandler.h"

#pragma pack (push, 1)

class TransportHeader
{
public:
    virtual void print() = 0;

protected:
    friend class PacketHandler;
    friend class AbstractPacket;
    virtual std::string getTransportType() = 0;
};

#pragma pack (pop)
