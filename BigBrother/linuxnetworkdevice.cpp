#include "linuxnetworkdevice.h"

NetworkDevice::NetworkDevice(std::string name,
    std::string address, bool isEnabled, size_t MTU) : name(name), addresStr(address),
    isEnabled(isEnabled), MTU(MTU) { ; }
