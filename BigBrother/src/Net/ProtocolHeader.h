#pragma once
#include "Common/packethandler.h"

#pragma pack(push, 1)

class ProtocolHeader{
public:
    virtual void print() = 0;
protected:
    friend class PacketHandler;
    friend class AbstractPacket;
    virtual std::string getProtocolType() = 0;
    virtual std::string getSourceIP() = 0;
    virtual std::string getDestIP() = 0;
};

#pragma pack(pop)
