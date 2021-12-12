#pragma once
#include <cstdint>
#include <vector>
#include "ProtocolHeader.h"

static size_t const addressLength = 16;

class IPv6Header : public ProtocolHeader
{
#ifdef __LITTLE_ENDIAN__
   std::uint8_t version : 4;
   std::uint8_t traficClass : 8;
   std::uint32_t flowLabel : 20;
   std::uint16_t payloadLength;
   std::uint8_t nextHeader;
   std::uint8_t hopLimit;

   unsigned char sourceAddress[addressLength], destinationAddress[addressLength];

#elif __BIG_ENDIAN__
    union
    {
    struct
    {
        std::uint32_t a;
        std::uint32_t b;


    }

    std::uint8_t version;
    std::uint8_t traficClass;
    std::uint32_t flowLabel;
    std::uint16_t payloadLength;
    std::uint8_t nextHeader;
    std::uint8_t hopLimit;
    }
    IPv6Header(std::vector<unsigned char> &buf)
    {
        char x = buf.begin();
    }
#endif
};
