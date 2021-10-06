#include "linuxdevicesmanager.h"

std::string LinuxDevicesManager::undef = "undefined";
size_t LinuxDevicesManager::defaultSize = 1500;

std::vector<NetworkDevice> LinuxDevicesManager::getDevices()
{
    std::vector<NetworkDevice> devices;
    std::filesystem::path netDevices = "////sys//class//net";

    for(auto &device : std::filesystem::directory_iterator(netDevices))
    {
        if (!device.is_directory())
        {
            continue;
        }

        std::string name = device.path();
        name = name.substr(name.find_last_of("//") + 1);

        std::string address = readAddr(device);
        size_t MTU = readMTU(device);
        bool state = readState(device);
        devices.emplace_back(name, address, state, MTU);
    }

    return devices;
}

std::string LinuxDevicesManager::readLine(std::string fileName)
{
    if (!std::filesystem::exists(fileName))
    {
        throw std::runtime_error("File doesn`t exist");
    }

    std::ifstream file(fileName);
    std::string result;
    file >> result;
    file.close();
    return result;
}

std::string LinuxDevicesManager::readAddr(std::filesystem::path p)
{
    std::string address;

    try{
        address = readLine(static_cast<std::string>(p) + "//address");
    }
    catch (std::runtime_error const &)
    {
        address = undef;
    }

    return address;
}

size_t LinuxDevicesManager::readMTU(std::filesystem::path p)
{
    std::string mtus;
    size_t mtui;

    try{
        mtus = readLine(static_cast<std::string>(p) + "//mtu");
        mtui = static_cast<size_t>(std::stoi(mtus));
    }
    catch (...)
    {
        mtui = defaultSize;
    }

    return mtui;
}

bool LinuxDevicesManager::readState(std::filesystem::path p)
{
    std::string states;
    bool stateb;

    try{
        states = readLine(static_cast<std::string>(p) + "//carrier");
        stateb = std::stoi(states);
    }
    catch (...)
    {
        stateb = false;
    }

    return stateb;
}
