#pragma once

#include <cstdint>
#include <string>
#include <vector>

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
//    std::vector<unsigned char> buf(&iIP);
//    std::string ip = "";

//    for (auto x = buf.rbegin(); x != buf.rend(); x++)
//    {
//        ip += std::to_string(*x) + '.';
//    }

//    ip.erase(ip.length() - 1, 1);
//    return ip;
}
