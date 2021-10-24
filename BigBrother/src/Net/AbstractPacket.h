#pragma once
#ifndef ABSTRACTPACKET
#define ABSTRACTPACKET

#include <memory>
#include "IPv4Header.h"
#include "EthernetIIHeader.h"
#include "TCPHeader.h"
#include "UDPHeader.h"

class AbstractPacket
{
private:
    std::unique_ptr<EthernetHeader> ethHeader;
    std::unique_ptr<ProtocolHeader> pHeader;
    std::unique_ptr<TransportHeader> tHeader;

public:
    AbstractPacket(std::unique_ptr<EthernetHeader> eHeader,
        std::unique_ptr<ProtocolHeader> pHeader, std::unique_ptr<TransportHeader> tHeader)
        : ethHeader(std::move(eHeader)), pHeader(std::move(pHeader)),
          tHeader(std::move(tHeader)) {;};

    void print()
    {
        if (ethHeader)
        {
            ethHeader->print();
        }

        if (pHeader)
        {
            pHeader->print();
        }

        if (tHeader)
        {
            tHeader->print();
        }
    }
};

#endif