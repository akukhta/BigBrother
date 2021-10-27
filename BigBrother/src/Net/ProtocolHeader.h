#pragma once
#include "Common/packethandler.h"
#pragma pack(push, 1)

class ProtocolHeader{
public:
    virtual void print() = 0;
protected:
    friend class PacketHandler;
};

#pragma pack(pop)
