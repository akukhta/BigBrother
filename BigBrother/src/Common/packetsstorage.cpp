#include "packetsstorage.h"

std::string const PacketsStorage::dataPath = "data";

PacketsStorage::PacketsStorage()
{
    auto settings = Settings::getInstance();
    maxSize = getSizeInBytes(settings->getSizeType(), settings->getMaxDumpSize());

    fd = open(dataPath.c_str(), O_RDWR | O_CREAT | O_TRUNC);

    if (fd == -1)
    {
        throw std::runtime_error("Can`t create data file");
    }

    if (ftruncate(fd, maxSize) != 0)
    {
        throw std::runtime_error("Cannot resize the data file");
    }

    data = static_cast<unsigned char*>(mmap(NULL, maxSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    if (data == MAP_FAILED)
    {
        throw std::runtime_error("File mapping error");
    }

    data[0] = 0xaa;
    data[1] = 0xbb;
    data[2] = 0xcc;
    data[3] = 0xdd;
    data[4] = 0xee;
    data[5] = 0xff;
}

PacketsStorage::~PacketsStorage()
{
    close(fd);
    munmap(data, maxSize);
    //Todo: delete the file here
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
