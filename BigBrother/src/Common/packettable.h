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
    void addRow(AbstractPacket &&packet);
private:
    QTableWidget *table;
    std::mutex tableMutex;
    static const QStringList headers;

};
