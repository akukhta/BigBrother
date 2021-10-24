#pragma once
#include <array>
#include <vector>
#include "EthernetHeader.h"
#define addressSize 6

class EnthernetIIHeader final: public EthernetHeader
{
public:
    EnthernetIIHeader(std::vector<unsigned char> &buffer);
    virtual void print() final override {;};

private:
    unsigned char destAddress[addressSize], sourceAddress[addressSize];
    unsigned short typeLength;
};

EnthernetIIHeader::EnthernetIIHeader(std::vector<unsigned char> &buffer)
{
    for(size_t i = 0; i < 6; i++)
    {
        destAddress[i] = buffer[i];
        sourceAddress[i] = buffer[i + addressSize];
    }

    typeLength = *reinterpret_cast<unsigned short*>(buffer.data() + addressSize * 2, buffer.data() + addressSize * 2 + sizeof(unsigned short));
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(EnthernetIIHeader) - sizeof(EthernetHeader));
}
