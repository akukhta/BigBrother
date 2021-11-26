#pragma once
#include <vector>
#include <memory>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <type_traits>
#include <bit>

template <typename T>
T const getFromBuffer(std::vector<unsigned char> const & buffer, std::endian castEndianness = std::endian::big,
    size_t offset = 0)
{
    if (offset >= buffer.size() || sizeof(T) + offset >= buffer.size())
    {
        throw std::runtime_error("");
    }

    if (std::endian::native == castEndianness)
    {
        return *reinterpret_cast<T const *>(buffer.data() + offset);
    }
    else
    {
        std::vector<unsigned char> tmp(buffer.data() + offset, buffer.data() + offset + sizeof(T));
        std::reverse(tmp.begin(), tmp.end());
        return *reinterpret_cast<T const *>(tmp.data());
    }
}

template <typename T>
T takeFromBuffer(std::vector<unsigned char> & buffer)
{
    T res = getFromBuffer<T>(buffer);
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(T));
    return res;
}

template <class T>
std::unique_ptr<T> getUniqueFromBuffer(std::vector<unsigned char> & buffer)
{
    T x = *reinterpret_cast<T*>(buffer.data());
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(T));
    return std::make_unique<T>(x);
}

template <class T, std::enable_if<std::is_same<T, std::uint32_t>::value>* = nullptr>
std::string intToIP(std::uint32_t iIP)
{
    std::uint8_t *iIPp = reinterpret_cast<std::uint8_t*>(&iIP);
    std::string ip = "";

    for (size_t _ = 0; _ < sizeof(iIP); _++)
    {
        ip += std::to_string(*iIPp) + '.';
        iIPp++;
    }

    ip.erase(ip.length() - 2, 1);
    return ip;
}
