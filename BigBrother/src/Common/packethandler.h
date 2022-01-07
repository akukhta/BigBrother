#pragma once
#ifndef PACKETHANDLER
#define PACKEDHANDLER

#include <queue>
#include <thread>
#include <mutex>

#include <condition_variable>
#include <memory>
#include <functional>
#include <fstream>
#include "Net/AbstractPacket.h"
#include "Common/packetsstorage.h"

class PacketHandler
{
public:
    PacketHandler(std::function<void (void*)> callback = nullptr, std::shared_ptr<PacketsStorage> storage = nullptr)
        : callback(callback), storage(storage)
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
    std::function<void (void*)> callback;
    std::ofstream out;
    std::shared_ptr<PacketsStorage> storage;
    void handle();
};

#endif
