#include "packethandler.h"
#include <functional>

void PacketHandler::startHandling()
{
    std::thread t([this](){handle();});
    t.detach();
}

void PacketHandler::addToQueue(std::vector<unsigned char> packet)
{
    queueMutex.lock();
    packets.push(packet);
    queueMutex.unlock();
    var.notify_one();
}

void PacketHandler::handle()
{
    while(true)
    {
        std::unique_lock<std::mutex> lk(this->queueMutex);
        var.wait(lk, [this]() -> bool {return !packets.empty();});
        auto packet = packets.front();

        std::unique_ptr<EthernetHeader> eHeader = std::make_unique<EnthernetIIHeader>(packet);
        std::unique_ptr<ProtocolHeader> pHeader = std::make_unique<IPv4Header>(packet);

        if (IPv4Header *ipv4 = dynamic_cast<IPv4Header*>(pHeader.get()))
        {

        }

        packets.pop();
        lk.unlock();
    }
}
