#pragma once
#include <array>
#include <vector>
#include "EthernetHeader.h"
#include "Common/utiles.h"

#define addressSize 6
#define ethernetHeaderTypeMinVal 1536
class EnthernetIIHeader final: public EthernetHeader
{
public:
    EnthernetIIHeader(std::vector<unsigned char> &buffer)
    {
        {
            for(size_t i = 0; i < 6; i++)
            {
                destAddress[i] = buffer[i];
                sourceAddress[i] = buffer[i + addressSize];
            }

            typeLength = getFromBuffer<unsigned short>(buffer, std::endian::big, addressSize * 2);
            buffer.erase(buffer.begin(), buffer.begin() + sizeof(EnthernetIIHeader) - sizeof(EthernetHeader));
        }
    };

    virtual void print() final override
    {
        ;
    };

    unsigned char destAddress[addressSize], sourceAddress[addressSize];
    unsigned short typeLength;

    type virtual getTypeID() override
    {
        switch (typeLength)
        {
            case type::ipv4:
            {
                return type::ipv4;
            }

            case type::ipv6:
            {
                return type::ipv6;
            }

            case type::ARP:
            {
                return type::ARP;
            }

            default:
            {
                return type::err;
            }
        }
    }

    static std::string macToStr(unsigned char mac[addressSize] )
    {
        auto isHex = Settings::getInstance()->getMacType() == Settings::viewType::HEX;

        std::stringstream ss;

        for (size_t i = 0; i < addressSize; i++)
        {
            if (isHex)
            {
                ss << std::hex << static_cast<int>(mac[i]) << ":";
            }
            else
            {
                ss << std::to_string(mac[i]) << ":";
            }
        }

        auto res = ss.str();
        res.erase(res.end() - 1, res.end());

        return res;
    }

    virtual std::string getType() override final
    {
        return "Enthernet II";
    };

    virtual std::string getSourceMac() override final
    {
        return EnthernetIIHeader::macToStr(sourceAddress);
    }

    virtual std::string getDestMac() override final
    {
        return EnthernetIIHeader::macToStr(destAddress);
    }

    virtual std::string getInfo() override final
    {
        std::stringstream sstream;
        sstream << "Ethernet II header's info: " << std::endl;
        sstream << "Destination MAC: " << getDestMac() << std::endl;
        sstream << "Source MAC: " << getSourceMac() << std::endl;
        sstream << "EtherType: " << static_cast<int>(typeLength) << std::endl;

        return sstream.str();
    }
};

