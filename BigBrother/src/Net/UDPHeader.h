#pragma once
#include <cstdint>
#include "TransportHeader.h"

class UDPHeader final : public TransportHeader
{
public:
    virtual void print() override {;};

private:
    std::uint16_t sourcePort;
    std::uint16_t destenationPort;
    std::uint16_t lengthOfData;
    std::uint16_t checksum;
};
