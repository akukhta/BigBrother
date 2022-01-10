#pragma once
#include <cstdint>
#include <bit>
#include "TransportHeader.h"


class TCPHeader final : public TransportHeader
{
public:
    virtual void print() override final {;};

    std::uint16_t sourcePort;
    std::uint16_t destinationPort;
    std::uint32_t sequenceNumber;
    std::uint32_t ackNumber;

#ifdef __BIG_ENDIAN__
    std::byte headerLength : 4;
    std::byte reservedBits : 4;
#else ifdef __LITTLE_ENDIAN__
    std::byte reservedBits : 4;
    std::byte headerLength : 4;
#endif

    struct flag
    {

#ifdef __BIG_ENDIAN__
        std::byte cwr : 1;
        std::byte ece : 1;
        std::byte urg : 1;
        std::byte ack : 1;
        std::byte psh : 1;
        std::byte rst : 1;
        std::byte syn : 1;
        std::byte fin : 1;

#else ifdef __LITTLE_ENDIAN__

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

    virtual std::string getTransportType() override final
    {
        return "TCP";
    }

    virtual std::string getSourcePort() override final
    {
        return std::to_string(sourcePort);
    }

    virtual std::string getDestPort() override final
    {
        return std::to_string(destinationPort);
    }

    virtual std::string getInfo() override final
    {
        std::stringstream sstream;

        sstream << "TCP header's info:" << std::endl;headerLength;

        sstream << "Source port: " << getSourcePort() << std::endl;
        sstream << "Destination port: " << getDestPort() << std::endl;
        sstream << "Source port: " << getSourcePort() << std::endl;
        sstream << "Sequence number: " << static_cast<int>(sequenceNumber) << std::endl;
        sstream << "Ack. number: " << static_cast<int>(ackNumber) << std::endl;
        sstream << "Reserved bits: " << static_cast<int>(reservedBits) << std::endl;
        sstream << "Header's length: " << static_cast<int>(headerLength) << std::endl;
        sstream << "Window size: " << static_cast<int>(windowSize) << std::endl;
        sstream << "Checksum: " << static_cast<int>(checkSum) << std::endl;
        sstream << "Urgent pointer: " << static_cast<int>(urgentPointer) << std::endl;
        sstream << "BITS:" << std::endl;
        sstream << "FIN: " << static_cast<int>(flags.fin) << std::endl;
        sstream << "SYN: " << static_cast<int>(flags.syn) << std::endl;
        sstream << "RST: " << static_cast<int>(flags.rst) << std::endl;
        sstream << "PSH: " << static_cast<int>(flags.ack) << std::endl;
        sstream << "URG: " << static_cast<int>(flags.urg) << std::endl;
        sstream << "ECE: " << static_cast<int>(flags.ece) << std::endl;
        sstream << "CWR: " << static_cast<int>(flags.cwr) << std::endl;

        return sstream.str();
    }
};
