#include "linuxnetworkdevice.h"

LinuxNetworkDevice::LinuxNetworkDevice(std::string name,
    std::string address, bool isEnabled, size_t MTU) : name(name), addresStr(address),
    isEnabled(isEnabled), MTU(MTU) { ; }
