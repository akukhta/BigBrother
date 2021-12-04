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
#include <unordered_map>
#include "Net/EthernetHeader.h"
#include "Net/ProtocolHeader.h"
#include "Net/TransportHeader.h"
#include "Common/littleendianparser.h"

//When we construct a header from vector of chars, we should fill buffer by zero vptrSize times!
static const size_t vptrSize = sizeof(void*);

//The Map contatins pairs of "hash of type, pointer to vptr"
//We have to put this ptr manually in case if we construct a header from buffer
static std::unordered_map<size_t, std::vector<unsigned char>> vptrsTable;

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

//Todo: add a table with sizes of all fields to make revert in case if we have little endian
template <class T, std::enable_if<std::is_base_of<T, EthernetHeader>::value || std::is_base_of<T, ProtocolHeader>::value ||
    std::is_base_of<T, TransportHeader>::value>* = nullptr>
std::unique_ptr<T> getUniqueFromBuffer(std::vector<unsigned char> & buffer)
{
    if (vptrsTable.find(typeid(T).hash_code()) == vptrsTable.end())
    {
        T tmp;
        unsigned char *tmpPtr = reinterpret_cast<unsigned char*>(&tmp);
        std::vector<unsigned char> vptr;

        for (size_t i = 0; i < vptrSize; i++)
        {
            vptr.push_back(tmpPtr[i]);
        }

        vptrsTable.insert(std::make_pair(typeid(T).hash_code(), std::move(vptr)));
    }

    std::vector<unsigned char> subVec(buffer.data(), buffer.data() + sizeof(T) - vptrSize);

#ifdef LITTLE_ENDIAN
    LittleEndianParser::getInstance();
#endif

    std::copy(vptrsTable.at(typeid(T).hash_code()).begin(), vptrsTable.at(typeid(T).hash_code()).end(),
              std::insert_iterator(subVec, subVec.begin()));

    T x = *reinterpret_cast<T*>(subVec.data());
    buffer.erase(buffer.begin(), buffer.begin() + sizeof(T) - vptrSize);
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
