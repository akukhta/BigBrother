#pragma once
#ifndef PACKETHANDLER
#define PACKEDHANDLER

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Net/AbstractPacket.h"

class PacketHandler
{
public:
    PacketHandler()
    {
        ;
    };
    void startHandling();
    void stopHandling();
    void addToQueue(std::vector<unsigned char> packet);

private:
    std::mutex queueMutex;
    std::condition_variable var;
    std::queue<std::vector<unsigned char>> packets;
    void handle();
};

#endif
