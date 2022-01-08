#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <cmath>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "Common/ViewSettings.h"
#include "Net/AbstractPacket.h"

class PacketsStorage
{
public:
    PacketsStorage();
    ~PacketsStorage();
    static size_t getSizeInBytes(size_t format, size_t size);
    std::vector<unsigned char> getDataByIndex(size_t index);
    void addPacket(std::unique_ptr<AbstractPacket> & packet, std::vector<unsigned char> const &packetsData);
    AbstractPacket const * getPacketByIndex(size_t index);

private:
    //Key value structure which stores "Packet's index" - "Packet's offset in binary file", "Data length"
    std::unordered_map<size_t, std::pair<size_t, size_t>> packetsOffset;
    std::unordered_map<size_t, std::unique_ptr<AbstractPacket>> packets;
    void save(std::vector<unsigned char> const &packetsData);
    size_t memUsed = 0, maxSize, currentPacket = 0;
    std::string static const dataPath;
    int fd;
    unsigned char *data;    
};
