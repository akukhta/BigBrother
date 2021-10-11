#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

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
