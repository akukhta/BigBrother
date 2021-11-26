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
        out << packet.size() << std::endl;
        std::string str(reinterpret_cast<char*>(packet.data()), packet.size());
        //terminal->printMessage(str);

        unsigned short ethernetHeaderLength;

        try
        {
            ethernetHeaderLength = getFromBuffer<unsigned short>(packet, std::endian::big, 12);
        }
        catch (std::runtime_error const &err)
        {
            packets.pop();
            lk.unlock();
            continue;
        }

        std::unique_ptr<EthernetHeader> eHeader;
        std::unique_ptr<ProtocolHeader> pHeader;
        std::unique_ptr<TransportHeader> tHeader;
        std::uint8_t ethernetHeaderType;

        if (ethernetHeaderLength >= ethernetHeaderTypeMinVal)
        {
            eHeader = std::make_unique<EnthernetIIHeader>(packet);
        }

        if (eHeader == nullptr)
        {
            packets.pop();
            lk.unlock();
            continue;
        }

        auto eHeaderType = eHeader->getTypeID();

        //Here is the problem. It uses cast to little-endian, need to avoid that.
        switch (eHeader->getTypeID())
        {
            case type::ipv4:
            {
                //Compare bytes and returned IPv4!
                pHeader = getUniqueFromBuffer<IPv4Header>(packet);

                if (pHeader == nullptr)
                {
                    int a = rand();
                    a++;
                }

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

            case type::ipv6:
            {
                int aaa;
                aaa = rand();
                aaa++;
            }
        }

        AbstractPacket aPacket(std::move(eHeader), std::move(pHeader), std::move(tHeader));
        callback(&aPacket);
        packets.pop();
        lk.unlock();
    }
}
