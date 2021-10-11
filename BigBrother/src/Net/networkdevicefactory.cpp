#include "networklistenerfactory.h"

std::unique_ptr<NetworkListener> getListener(NetworkDevice device,
    std::shared_ptr<PacketTable> const &table, std::function<void (std::vector<unsigned char>)> handlerFunc)
{
    std::unique_ptr<NetworkListener> listener;

    #ifdef __unix
    listener = std::make_unique<NetworkListenerLin>(table, device, handlerFunc);
    #endif

    return listener;
}
