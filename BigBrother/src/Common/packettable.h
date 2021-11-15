#pragma once

#include <memory>
#include <QTableWidget>
#include <mutex>
#include "Net/AbstractPacket.h"

//Packet table
class PacketTable
{
public:
    PacketTable(QTableWidget *table);
    std::function<void (void*)> getPrintFunction();

private:
    QTableWidget *table;
    std::mutex tableMutex;
    static const QStringList headers;
    void addRow(void *packet);

};
