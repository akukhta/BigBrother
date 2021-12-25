#pragma once

#include <cstdint>
#include <string>
#include <vector>
//#include "Common/ViewSettings.h"

static size_t const addressLength = 16;

std::string inline intToIP(std::uint32_t iIP)
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
