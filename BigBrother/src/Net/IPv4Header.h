#pragma once
#include <bit>
#include <cstdint>
#include <vector>
#include "ProtocolHeader.h"
#include "Common/utiles.h"

enum class protocol: std::uint8_t
{
    TCP = 6,
    UDP = 17,
};

class IPv4Header final : public ProtocolHeader
{
public:

    IPv4Header(std::vector<unsigned char> &buffer)
    {
        length = buffer[0] >> 4;
        version = (buffer[0] << 4) >> 4;

        DSCP = buffer[1] >> 2;
        ECN = (buffer[1] << 6) >> 6;

        buffer.erase(buffer.begin(), buffer.begin() + 2);

        totalLength = takeFromBuffer<std::uint16_t>(buffer);
        id = takeFromBuffer<std::uint16_t>(buffer);

        {
            std::uint16_t x = takeFromBuffer<std::uint16_t>(buffer);
        }

    };

    virtual void print() override final {;};
private:

#if defined(__ORDER_LITTLE_ENDIAN__)
    std::uint8_t length : 4;
    std::uint8_t version : 4;
#elif defined(__ORDER_BIG_ENDIAN__)
    std::uint8_t version : 4;
    std::uin8_t length : 4;
#endif

    std::uint8_t DSCP : 6;
    std::uint8_t ECN : 2;
    std::uint16_t totalLength;
    std::uint16_t id;
    std::uint16_t flags : 3;
    std::uint16_t offset : 13;
    std::uint8_t ttl;
    std::uint8_t protocol;
    std::uint16_t checkSum;
    std::uint32_t sourceAddress;
    std::uint32_t destAddress;
};
