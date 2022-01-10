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

void PacketViewer::printPacket(const std::string &data)
{
    ui->textBrowser->clear();
    ui->textBrowser->append(QString::fromStdString(data));
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

    for (int i = tmp.length() - 1, j = res.length() - 1; i >= 0 && j >= 0; i--, j--)
    {
        res[j] = tmp[i];
    }

    return res;
}
