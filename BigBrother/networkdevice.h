#pragma once
#include <vector>
#include <string>

//Network device abstraction class
class NetworkDevice
{
public:
    NetworkDevice(std::string name, std::string address, bool isEnabled, size_t MTU);
    std::string name;
    std::string addresStr;
    bool isEnabled;
    size_t MTU;
};

