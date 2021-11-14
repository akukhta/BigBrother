#include "packettable.h"

const QStringList PacketTable::headers{"Ethernet frame", "Protocol type", "Transport type",
    "Source MAC", "Destination MAC", "Source IP", "Destination IP"};

PacketTable::PacketTable(QTableWidget *table) : table(table)
{
    table->setColumnCount(7);
    table->setVerticalHeaderLabels(PacketTable::headers);
}

void PacketTable::addRow(AbstractPacket &&packet)
{
    //std::unique_lock<std::mutex> lk(tableMutex);
    size_t rowCount = table->rowCount();
    table->setRowCount(rowCount + 1);
    table->insertRow(rowCount);
    table->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(packet.getEthernetHeaderType())));
    table->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(packet.getProtocolType())));
    table->setItem(rowCount, 2, new QTableWidgetItem(QString::fromStdString(packet.getTransportType())));
    table->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(packet.getSourceMAC())));
    table->setItem(rowCount, 4, new QTableWidgetItem(QString::fromStdString(packet.getDestMAC())));
    table->setItem(rowCount, 5, new QTableWidgetItem(QString::fromStdString(packet.getSourceIP())));
    table->setItem(rowCount, 6, new QTableWidgetItem(QString::fromStdString(packet.getDestIP())));
}
