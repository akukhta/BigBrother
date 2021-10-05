#pragma once
#include <vector>
#include <string>
#include "lindeviceswidges.h"

class LinuxNetworkDevice
{
public:
    LinuxNetworkDevice(std::string name, std::string address, bool isEnabled, size_t MTU);

private:
    std::string name, addresStr;
    bool isEnabled;
    size_t MTU;
};

