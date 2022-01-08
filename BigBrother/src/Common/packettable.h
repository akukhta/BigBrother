#pragma once

#include <memory>
#include <QTableWidget>
#include <mutex>
#include "Net/AbstractPacket.h"
#include "packetsstorage.h"

//Packet table
class PacketTable
{
public:
    PacketTable(QTableWidget *table, std::shared_ptr<PacketsStorage> packetsStorage = nullptr);
    std::function<void (void*)> getPrintFunction();
    void clicked(size_t indx);
    void setPrintFunction(std::function<void(std::string const &)> func);

private:
    QTableWidget *table;
    std::mutex tableMutex;
    static const QStringList headers;
    void addRow(void *packet);
    std::shared_ptr<PacketsStorage> packetsStorage;
    std::function<void(std::string const &)> printerFunction;
};
