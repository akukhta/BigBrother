#pragma once
#include <vector>
#include <filesystem>
#include <fstream>
#include "linuxnetworkdevice.h"

class LinuxDevicesManager
{
public:
    LinuxDevicesManager() = delete;
    static std::vector<LinuxNetworkDevice> getDevices();

private:
    static std::string readLine(std::string fileName);
    static std::string readAddr(std::filesystem::path p);
    static size_t readMTU(std::filesystem::path p);
    static bool readState(std::filesystem::path p);
    static std::string undef;
    static size_t defaultSize;
};

