#include "packettable.h"

const QStringList PacketTable::headers{"Ethernet frame", "Protocol type", "Transport type",
    "Source MAC", "Destination MAC", "Source IP", "Destination IP"};

PacketTable::PacketTable(QTableWidget *table) : table(table)
{
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels(PacketTable::headers);
    table->setRowCount(0);
}

std::function<void (void*)> PacketTable::getPrintFunction()
{
    std::function<void (void*)> r = [this](void *p){
        addRow(p);
    };
    return r;
}

void PacketTable::addRow(void *packet)
{
    std::unique_lock<std::mutex> lk(tableMutex);
    size_t rowCount = table->rowCount();
    AbstractPacket *_packet = reinterpret_cast<AbstractPacket*>(packet);
    table->insertRow(table->rowCount());
    table->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(_packet->getEthernetHeaderType())));
    table->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(_packet->getProtocolType())));
    table->setItem(rowCount, 2, new QTableWidgetItem(QString::fromStdString(_packet->getTransportType())));
    table->setItem(rowCount, 3, new QTableWidgetItem(QString::fromStdString(_packet->getSourceMAC())));
    table->setItem(rowCount, 4, new QTableWidgetItem(QString::fromStdString(_packet->getDestMAC())));
    table->setItem(rowCount, 5, new QTableWidgetItem(QString::fromStdString(_packet->getSourceIP())));
    table->setItem(rowCount, 6, new QTableWidgetItem(QString::fromStdString(_packet->getDestIP())));
}
