#pragma once
#include <cstdint>
#include "TransportHeader.h"

class UDPHeader final : public TransportHeader
{
public:
    virtual void print() override {;};

    std::uint16_t sourcePort;
    std::uint16_t destenationPort;
    std::uint16_t lengthOfData;
    std::uint16_t checksum;

    virtual std::string getTransportType() override
    {
        return "UDP";
    }

    virtual std::string getSourcePort() override
    {
        return std::to_string(sourcePort);
    }

    virtual std::string getDestPort() override
    {
        return std::to_string(destenationPort);
    }
};
