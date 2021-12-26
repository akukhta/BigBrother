#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "Common/ViewSettings.h"

//Todo: add port and other lines to hex or dec converting

static size_t const addressLength = 16;

std::string inline intToIPDec(std::uint32_t iIP)
{
    std::vector<std::string> octets;
    std::string ip = "";

    std::uint8_t *it = reinterpret_cast<uint8_t*>(&iIP);

    for (size_t c = 0; c < sizeof(iIP); c++)
    {
        octets.push_back(std::to_string(*it));
        it++;
    }

    for (auto x = octets.rbegin(); x != octets.rend(); x++)
    {
        ip += *x;
        ip += ".";
    }

    ip.erase(ip.length() - 1, 1);

    return ip;
}

std::string inline intToIPHex(std::uint32_t iIP)
{
    std::stringstream ss;
    ss << std::hex;
    std::uint8_t *it = reinterpret_cast<uint8_t*>(&iIP);
    std::string res;

    for (size_t i = 0; i < sizeof(iIP); i++)
    {
        ss << std::hex << static_cast<int>(it[i]) << ":";
        auto tmpStr = ss.str();

        res.insert(res.begin(), tmpStr.begin(), tmpStr.end());
        ss.str("");
    }

    res.erase(res.end() - 1, res.end());

    return res;
}

std::string inline intToIP(std::uint32_t iIP)
{
    return Settings::getInstance()->getIPType() == Settings::viewType::DEC ? intToIPDec(iIP) : intToIPHex(iIP);
}

std::string inline getIPv6IP(unsigned char addres[addressLength])
{
    std::string res = "";
    unsigned char index = 0;
    std::for_each_n(addres, addressLength, [&](auto x) {
        res += std::to_string(x);
        index++;

        if (index % 2 == 0)
        {
            index = 0;
            res += ":";
        }
    });

    res.erase(res.length() - 1, 1);
    return res;
}
