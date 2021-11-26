#pragma once
#include <cstdint>
#include "ProtocolHeader.h"

class IPv6Header : public ProtocolHeader
{
#ifdef __LITTLE_ENDIAN__
   std::uint8_t version : 4;
   std::uint8_t traficClass : 8;
   std::uint32_t flowLabel : 20;
#elif __BIG_ENDIAN__
   //TODO: add enum
#endif
};
