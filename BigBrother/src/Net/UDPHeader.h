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

    virtual std::string getTransportType() override final
    {
        return "UDP";
    }

    virtual std::string getSourcePort() override final
    {
        return std::to_string(sourcePort);
    }

    virtual std::string getDestPort() override final
    {
        return std::to_string(destenationPort);
    }

    virtual std::string getInfo() override final
    {
        std::stringstream sstream;

        sstream << "UDP header's info:" << std::endl;
        sstream << "Source port: " << getSourcePort() << std::endl;
        sstream << "Destination port: " << getDestPort() << std::endl;
        sstream << "Data's length: " << static_cast<int>(lengthOfData) << std::endl;
        sstream << "Checksum: " << static_cast<int>(checksum) << std::endl;

        return sstream.str();
    }
};
