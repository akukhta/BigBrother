#pragma once
#include <cstdint>
#include <vector>
#include "ProtocolHeader.h"

static size_t const _addressLength = 16;


//Looks like beltelecom doesn`t support IPv6, don`t know how to test it, lol
//Maybe will make an utily to send an ipv6 packet to localhost

class IPv6Header : public ProtocolHeader
{
public:
    virtual void print() override
    {
        ;
    }

private:
   using u128 = unsigned char[_addressLength];

   std::uint32_t version : 4;
   std::uint32_t traficClass : 8;
   std::uint32_t flowLabel : 20;
   std::uint16_t payloadLength;
   std::uint8_t nextHeader;
   std::uint8_t hopLimit;

   u128 sourceAddress, destinationAddress;

#ifdef __BIG_ENDIAN__
   //Need to test if it works correctly
   void transform()
   {
       std::uint8_t : 4 tmp1 = traficClass >> 4, tmp2 = (traficClass << 4) >> 4;
       traficClass = version ^ (flowLabel >> 16);
       version = tmp;
       flowLabel = tmp2 ^ flowLabel >> 4;
   }
#endif

   virtual std::string getProtocolType() override
   {
       return "IPv6";
   }

   virtual std::string getSourceIP() override
   {
       return getIPv6IP(sourceAddress);
   }

   virtual std::string getDestIP() override
   {
       return getIPv6IP(destinationAddress);
   }
};
