//#ifdef __LITTLE_ENDIAN__

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

class LittleEndianParser : public std::enable_shared_from_this<LittleEndianParser>
{
public:

    static std::shared_ptr<LittleEndianParser> getInstance()
    {
        if (instance == nullptr)
        {
            instance = std::make_shared<LittleEndianParser>();
        }

        return instance;
    };

    std::vector<unsigned short> getMap(unsigned short key)
    {
        return reversingMap.at(key);
    }

private:
    LittleEndianParser()
    {
        //IPv4 map
        reversingMap.insert(std::make_pair(0,
            std::vector<unsigned short>({1, 1, 2, 2, 2, 1, 1, 2, 4, 4})));

        //IPv6 map
        reversingMap.insert(std::make_pair(1,
            std::vector<unsigned short>({1, 1, 2, 2, 1, 1, 4, 4})));

        //TCP map
        reversingMap.insert(std::make_pair(2,
            std::vector<unsigned short>({2, 2, 4, 4, 2, 2, 2, 2})));

        //UDP map
        reversingMap.insert(std::make_pair(3,
            std::vector<unsigned short>({2, 2, 2, 2})));
    };

    static std::shared_ptr<LittleEndianParser> instance;
    std::unordered_map<unsigned short, std::vector<unsigned short>> reversingMap;
};

std::shared_ptr<LittleEndianParser> LittleEndianParser::instance = nullptr;
//#endif
