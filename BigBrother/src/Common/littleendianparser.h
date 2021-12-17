//#ifdef __LITTLE_ENDIAN__

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "Net/IPv4Header.h"
#include "Net/IPv6Header.h"
#include "Net/TCPHeader.h"
#include "Net/UDPHeader.h"

class LittleEndianParser : public std::enable_shared_from_this<LittleEndianParser>
{
public:

    static std::shared_ptr<LittleEndianParser> getInstance()
    {
        static std::shared_ptr<LittleEndianParser> instance(new LittleEndianParser);
        return instance;
    };

    template <class T>
    std::vector<unsigned short> getMap()
    {
        return reversingMap.at(typeid(T).hash_code());
    }

private:
    LittleEndianParser()
    {
        //IPv4 map
        reversingMap.insert(std::make_pair(typeid(IPv4Header).hash_code(),
            std::vector<unsigned short>({1, 1, 2, 2, 2, 1, 1, 2, 4, 4})));

        //IPv6 map
        reversingMap.insert(std::make_pair(typeid(IPv6Header).hash_code(),
            std::vector<unsigned short>({1, 1, 2, 2, 1, 1, 16, 16})));

        //TCP map
        reversingMap.insert(std::make_pair(typeid(TCPHeader).hash_code(),
            std::vector<unsigned short>({2, 2, 4, 4, 2, 2, 2, 2})));

        //UDP map
        reversingMap.insert(std::make_pair(typeid(UDPHeader).hash_code(),
            std::vector<unsigned short>({2, 2, 2, 2})));
    };

    std::unordered_map<size_t, std::vector<unsigned short>> reversingMap;
};
//#endif
