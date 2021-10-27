#pragma once
#include "Common/packethandler.h"

#pragma pack (push, 1)

class TransportHeader
{
public:
    virtual void print() = 0;
private:
    friend class PacketHandler;
};

#pragma pack (pop)
