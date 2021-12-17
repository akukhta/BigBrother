#pragma once
#include <cstdint>
#include <bit>
#include "TransportHeader.h"


class TCPHeader final : public TransportHeader
{
public:
    virtual void print() override final {;};
private:
    std::uint16_t sourcePort;
    std::uint16_t destinationPort;
    std::uint32_t sequenceNumber;
    std::uint32_t ackNumber;

#if defined (__BIG_ENDIAN__)
    std::byte headerLength : 4;
    std::byte reservedBits : 4;
#elif defined (__LITTLE_ENDIAN__)
    std::byte reservedBits : 4;
    std::byte headerLength : 4;
#endif

    struct flag
    {

#if defined (__BIG_ENDIAN__)
        std::byte cwr : 1;
        std::byte ece : 1;
        std::byte urg : 1;
        std::byte ack : 1;
        std::byte psh : 1;
        std::byte rst : 1;
        std::byte syn : 1;
        std::byte fin : 1;

#elif defined (__LITTLE_ENDIAN__)

        std::byte fin : 1;
        std::byte syn : 1;
        std::byte rst : 1;
        std::byte psh : 1;
        std::byte ack : 1;
        std::byte urg : 1;
        std::byte ece : 1;
        std::byte cwr : 1;
#endif

    } flags;

    std::uint16_t windowSize;
    std::uint16_t checkSum;
    std::uint16_t urgentPointer;

    virtual std::string getTransportType() override
    {
        return "TCP";
    }

    virtual std::string getSourcePort() override
    {
        return std::to_string(sourcePort);
    }

    virtual std::string getDestPort() override
    {
        return std::to_string(destinationPort);
    }
};
