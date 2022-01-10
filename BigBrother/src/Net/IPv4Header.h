#pragma once
#include <bit>
#include <cstdint>
#include <vector>
#include "ProtocolHeader.h"
#include "Common/StringUtiles.h"

enum protocol
{
    TCP = 6,
    UDP = 17,
};

class IPv4Header final : public ProtocolHeader
{
public:
    virtual std::string getInfo() override final
    {
        std::stringstream result;

        result << "IPv4 Header's info:" << std::endl;
        result << "Length: " << static_cast<int>(length) << std::endl;
        result << "Version: " << static_cast<int>(version) << std::endl;
        result << "DSCP: " << static_cast<int>(DSCP) << std::endl;
        result << "ECN: " << static_cast<int>(ECN)<< std::endl;
        result << "Total length: " << static_cast<int>(totalLength) << std::endl;
        result << "ID: " << static_cast<int>(id) << std::endl;
        result << "flags: " << static_cast<int>(flags) << std::endl;
        result << "offset: " << static_cast<int>(offset) << std::endl;
        result << "ttl: " << static_cast<int>(ttl) << std::endl;
        result << "protocol: " << static_cast<int>(protocol) << std::endl;
        result << "checksum: " << static_cast<int>(checkSum) << std::endl;
        result << "source address: " << getSourceIP() << std::endl;
        result << "destination address: " << getDestIP() << std::endl;

        return result.str();
     };

#ifdef LITTLE_ENDIAN
    std::uint8_t length : 4;
    std::uint8_t version : 4;
#elif defined(BIG_ENDIAN)
    std::uint8_t version : 4;
    std::uin8_t length : 4;
#endif

#ifdef LITTLE_ENDIAN
    std::uint8_t DSCP : 6;
    std::uint8_t ECN : 2;
#elif defined(BIG_ENDIAN)
    std::uint8_t ECN : 2;
    std::uint8_t DSCP : 6;
#endif
    std::uint16_t totalLength;
    std::uint16_t id;
#ifdef LITTLE_ENDIAN
    std::uint16_t flags : 3;
    std::uint16_t offset : 13;
#elif defined(BIG_ENDIAN)
    std::uint16_t offset : 13;
    std::uint32_t flags : 3;
#endif
    std::uint8_t ttl;
    std::uint8_t protocol;
    std::uint16_t checkSum;
    std::uint32_t sourceAddress;
    std::uint32_t destAddress;

    virtual std::string getProtocolType() override final
    {
        return "IPv4";
    }

    virtual std::string getSourceIP() override final
    {
        return intToIP(sourceAddress);
    }

    virtual std::string getDestIP() override final
    {
        return intToIP(destAddress);
    }
};
