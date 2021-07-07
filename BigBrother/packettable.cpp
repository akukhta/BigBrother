#include "packettable.h"

const QStringList PacketTable::headers{"Text"};

PacketTable::PacketTable(QTableWidget *table) : table(table)
{
    table->setColumnCount(1);
    table->setVerticalHeaderLabels(PacketTable::headers);
}

void PacketTable::addRow(std::string data)
{
    std::unique_lock<std::mutex> lk(tableMutex);
    size_t rowCount = table->rowCount();
    table->setRowCount(rowCount + 1);
    table->insertRow(rowCount);
    table->setItem(rowCount, 0, new QTableWidgetItem(data.c_str()));
}
