#pragma once
#include "Common/packethandler.h"

enum type
{
    ipv4 = 0x0800,
    ipv6 = 0x86DD,
    ARP = 0x0806,
    err = 0xFFFF,
};

#pragma pack(push, 1)

class EthernetHeader
{
public:
    virtual void print() = 0;

private:
    friend class PacketHandler;
    type virtual getTypeID() = 0;
};

#pragma pack(pop)
