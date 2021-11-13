#pragma once
#ifndef PACKETHANDLER
#define PACKEDHANDLER

#include <queue>
#include <thread>
#include <mutex>

#include <condition_variable>
#include "Net/AbstractPacket.h"
#include "GUI/terminal.h"

class PacketHandler
{
public:
    PacketHandler(std::shared_ptr<Terminal> terminal = nullptr)
        : terminal(terminal)
    {
        out.open("sizes.txt");
    };

    void startHandling();
    void stopHandling();
    void addToQueue(std::vector<unsigned char> packet);
    ~PacketHandler(){out.close();};

private:
    std::mutex queueMutex;
    std::condition_variable var;
    std::queue<std::vector<unsigned char>> packets;
    std::shared_ptr<Terminal> terminal;
    std::ofstream out;
    void handle();
};

#endif
