#pragma once
#include <bit>
#include <cstdint>
#include "ProtocolHeader.h"

class IPv4Header final : public ProtocolHeader
{
public:
    virtual void print() override final {;};
private:

#if defined(__ORDER_LITTLE_ENDIAN__)
    std::byte length : 4;
    std::byte version : 4;
#elif defined(__ORDER_BIG_ENDIAN__)
    std::byte version : 4;
    std::byte length : 4;
#endif

    std::byte DSCP : 6;
    std::byte ECN : 2;
    std::uint16_t totalLength;
    std::uint16_t id;
    std::uint16_t flags : 3;
    std::uint16_t offset : 13;
    std::byte ttl;
    std::byte protocol;
    std::uint16_t checkSum;
    std::uint32_t sourceAddress;
    std::uint32_t destAddress;
};
