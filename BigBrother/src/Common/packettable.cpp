#include "packettable.h"

const QStringList PacketTable::headers{"Ethernet frame", "Protocol type", "Transport type",
    "Source MAC", "Destination MAC", "Source IP", "Destination IP", "Source port", "Destination port"};

PacketTable::PacketTable(QTableWidget *table, std::shared_ptr<PacketsStorage> packetsStorage) : table(table) , packetsStorage(packetsStorage)
{
    table->setColumnCount(9);
    table->setHorizontalHeaderLabels(PacketTable::headers);
    table->setRowCount(0);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

std::function<void (void*)> PacketTable::getPrintFunction()
{
    std::function<void (void*)> r = [this](void *p){
        addRow(p);
    };
    return r;
}

void PacketTable::clicked(size_t indx)
{
    AbstractPacket const * packet = packetsStorage->getPacketByIndex(indx);
    printerFunction(packet ? packet->getInfo() : "The packed has been deleted");
}

void PacketTable::setPrintFunction(std::function<void (const std::string &)> func)
{
    printerFunction = func;
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
    table->setItem(rowCount, 7, new QTableWidgetItem(QString::fromStdString(_packet->getSourcePort())));
    table->setItem(rowCount, 8, new QTableWidgetItem(QString::fromStdString(_packet->getDestPort())));
}
