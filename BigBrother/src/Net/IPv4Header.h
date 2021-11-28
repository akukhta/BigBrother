#pragma once
#include <bit>
#include <cstdint>
#include <vector>
#include "ProtocolHeader.h"
#include "Common/utiles.h"

enum protocol
{
    TCP = 6,
    UDP = 17,
};

class IPv4Header final : public ProtocolHeader
{
public:
    virtual void print() override final {;};

private:

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

    friend class PacketHandler;

    virtual std::string getProtocolType() override
    {
        return "IPv4";
    }

    virtual std::string getSourceIP() override
    {
        return intToIP<std::uint32_t>(sourceAddress);
    }

    virtual std::string getDestIP() override
    {
        return intToIP<std::uint32_t>(destAddress);
    }
};
