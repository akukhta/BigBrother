#pragma once

#include <memory>
#include <QTableWidget>
#include <mutex>

//Packet table
class PacketTable
{
public:
    PacketTable(QTableWidget *table);
    void addRow(std::string data);
private:
    QTableWidget *table;
    std::mutex tableMutex;
    static const QStringList headers;

};
