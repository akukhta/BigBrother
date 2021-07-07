#define pragma_once

#include <memory>
#include <QTableWidget>
#include <mutex>

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
