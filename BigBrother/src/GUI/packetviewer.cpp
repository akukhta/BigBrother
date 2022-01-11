#include "packetviewer.h"
#include "ui_packetviewer.h"

PacketViewer::PacketViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PacketViewer)
{

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->resizeColumnsToContents();

    QStringList vLabels;

    for (size_t i = 1; i <= 8; i++)
    {
        vLabels.push_back(intToHex(i));
    }

    vLabels.push_back("ASCII");

    ui->tableWidget->setHorizontalHeaderLabels(vLabels);
}

void PacketViewer::printPacket(const std::string &packet, std::vector<unsigned char> const &data)
{
    ui->textBrowser->clear();
    ui->textBrowser->append(QString::fromStdString(packet));
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    size_t elementsCount = 0;

    for(size_t i = 0; i < data.size(); i++)
    {
        if (elementsCount == 0)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        }

        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i % 8, new QTableWidgetItem(intToHex(static_cast<int>(data[i]), 0)));
        elementsCount++;

        if (elementsCount == 8)
        {
            elementsCount = 0;
        }
    }

    if (data.size() % 8)
    {
        for (size_t i = (data.size() % 8) - 1; i < 8; i++)
        {
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i, new QTableWidgetItem(intToHex(0, 0)));
        }
    }
}

PacketViewer::~PacketViewer()
{
    delete ui;
}

QString PacketViewer::intToHex(int num, short countOfZeroes)
{
    QString res = "0x";

    for (size_t i = 0; i < countOfZeroes; i++)
    {
        res += '0';
    }

    QString tmp = QString::number(num);

    if (countOfZeroes > 0)
    {
        for (int i = tmp.length() - 1, j = res.length() - 1; i >= 0 && j >= 0; i--, j--)
        {
            res[j] = tmp[i];
        }
    }
    else
    {
        for (size_t i = 0; i < tmp.length(); i++)
        {
            res += tmp[i];
        }
    }

    return res;
}
