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
        packets.pop();
        lk.unlock();
    }
}
