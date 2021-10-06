#pragma once
#include <vector>
#include <string>

class NetworkDevice
{
public:
    NetworkDevice(std::string name, std::string address, bool isEnabled, size_t MTU);
    std::string name;
private:
    std::string addresStr;
    bool isEnabled;
    size_t MTU;
};

