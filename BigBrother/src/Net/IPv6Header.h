#pragma once
#include <cstdint>
#include <vector>
#include "ProtocolHeader.h"

class IPv6Header : public ProtocolHeader
{
#ifdef __LITTLE_ENDIAN__
   std::uint8_t version : 4;
   std::uint8_t traficClass : 8;
   std::uint32_t flowLabel : 20;

   IPv6Header(std::vector<unsigned char> &buf)
   {


   }

#elif __BIG_ENDIAN__
    IPv6Header(std::vector<unsigned char> &buf)
    {
        char x = buf.begin();
    }
#endif
};
