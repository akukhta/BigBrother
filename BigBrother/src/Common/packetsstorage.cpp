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

void PacketsStorage::save(const std::vector<unsigned char> &packetsData)
{
    if (memUsed + packetsData.size() > maxSize)
    {
        memUsed = 0;
        packetsOffset.clear();
        packets.clear();
    }

    packetsOffset.insert(std::make_pair(currentPacket, std::make_pair(memUsed, memUsed + packetsData.size())));
    std::copy(packetsData.begin(), packetsData.end(), data + memUsed);
    memUsed += packetsData.size();
}

void PacketsStorage::addPacket(std::unique_ptr<AbstractPacket> & packet, std::vector<unsigned char> const &packetsData)
{
    packets.insert(std::make_pair(currentPacket, std::move(packet)));
    save(packetsData);
    currentPacket++;
}

const AbstractPacket *PacketsStorage::getPacketByIndex(size_t index)
{
    auto packet = packets.find(index);
    return packet != packets.end() ? packet->second.get() : nullptr;
}

std::vector<unsigned char> PacketsStorage::getDataByIndex(size_t index)
{
    auto offset = packetsOffset.find(index);

    return offset == packetsOffset.end() ? std::vector<unsigned char>() : std::vector<unsigned char>(data + offset->second.first, data + (offset->second.first + offset->second.second));
}
