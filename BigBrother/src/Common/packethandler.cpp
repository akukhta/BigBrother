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

        unsigned short ethernetHeaderLength = getFromBuffer<unsigned short>(packet, 20);
        std::unique_ptr<EthernetHeader> eHeader;
        std::unique_ptr<ProtocolHeader> pHeader;
        std::unique_ptr<TransportHeader> tHeader;
        std::uint8_t ethernetHeaderType;

        if (ethernetHeaderLength <= 1518)
        {
            eHeader = std::make_unique<EnthernetIIHeader>(packet);
        }

        switch (eHeader->getTypeID())
        {
            case type::ipv4:
            {
                pHeader = getUniqueFromBuffer<IPv4Header>(packet);

                switch (dynamic_cast<IPv4Header*>(pHeader.get())->protocol)
                {
                    case TCP:
                    {
                        tHeader = getUniqueFromBuffer<TCPHeader>(packet);
                        break;
                    }

                    case UDP:
                    {
                        tHeader = getUniqueFromBuffer<UDPHeader>(packet);
                        break;
                    }
                }

                break;
            }
        }

        packets.pop();
        lk.unlock();
    }
}
