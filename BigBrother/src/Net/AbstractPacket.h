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
    std::vector<unsigned char> data;

public:
    AbstractPacket(std::unique_ptr<EthernetHeader> eHeader,
        std::unique_ptr<ProtocolHeader> pHeader, std::unique_ptr<TransportHeader> tHeader, std::vector<unsigned char> &&data = std::vector<unsigned char>())
        : ethHeader(std::move(eHeader)), pHeader(std::move(pHeader)),
          tHeader(std::move(tHeader)), data(data) {;};

    std::string getInfo()
    {
        std::string result = "";

//        if (ethHeader)
//        {
//            ethHeader->print();
//        }

        if (pHeader)
        {
            result += pHeader->getInfo();
        }

//        if (tHeader)
//        {
//            tHeader->print();
//        }

        return result;
    }

    std::string getEthernetHeaderType()
    {
        return ethHeader != nullptr ? ethHeader->getType() : "";
    };

    std::string getSourceMAC()
    {
        return ethHeader != nullptr ?  ethHeader->getSourceMac() : "";
    }

    std::string getDestMAC()
    {
        return ethHeader != nullptr ? ethHeader->getDestMac() : "";
    }

    std::string getProtocolType()
    {
        return pHeader != nullptr ? pHeader->getProtocolType() : "";
    }

    std::string getTransportType()
    {
        return tHeader != nullptr ? tHeader->getTransportType() : "";
    }

    std::string getSourceIP()
    {
        return pHeader != nullptr ? pHeader->getSourceIP() : "";
    }

    std::string getDestIP()
    {
        return pHeader != nullptr ? pHeader->getDestIP() : "";
    }

    std::string getSourcePort()
    {
        return tHeader != nullptr ? tHeader->getSourcePort() : "";
    }

    std::string getDestPort()
    {
        return tHeader != nullptr ? tHeader->getDestPort() : "";
    }
};

#endif
