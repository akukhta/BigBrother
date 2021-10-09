#pragma once

#ifdef __unix
    #include "Linux/networklistenerlin.h"
#endif

//Function to get listeners for each OS
std::unique_ptr<NetworkListener> getListener(NetworkDevice device, std::shared_ptr<PacketTable> const &table);
