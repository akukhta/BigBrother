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
    std::unique_ptr<AbstractPacket> getPacketByIndex(size_t index);

private:
    //Key value structure which stores "Packet's index" - "Packet's offset in binary file"
    std::unordered_map<size_t, size_t> packetsOffset;
    size_t currentOffset = 0, maxSize;
    std::string static const dataPath;
    int fd;
    unsigned char *data;
};
