#include "packetsstorage.h"

PacketsStorage::PacketsStorage()
{
    auto settings = Settings::getInstance();
    maxSize = getSizeInBytes(settings->getSizeType(), settings->getMaxDumpSize());
}

// 0 - byte
// 1 - kilobyte
// 2 - megabyte
// 3 - gigabyte
// 4+ - etc
size_t PacketsStorage::getSizeInBytes(size_t format, size_t size)
{
    return size * pow(1024, format);
}

std::unique_ptr<AbstractPacket> PacketsStorage::getPacketByIndex(size_t index)
{
    return nullptr;
}
