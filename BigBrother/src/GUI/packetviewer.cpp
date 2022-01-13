#include "packetviewer.h"
#include "ui_packetviewer.h"

PacketViewer::PacketViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PacketViewer)
{

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(17);
    ui->tableWidget->resizeColumnsToContents();

    QStringList vLabels;

    for (size_t i = 0; i < 16; i++)
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
    ui->tableWidget->setRowCount(0);
    vLabels.clear();

    for(size_t i = 0; i < ceil(static_cast<double>(data.size()) / 16); i++)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString textView = "";

        for (size_t j = 0; j < 16; j++)
        {
            if (i * 16 + j < data.size())
            {
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, j, new QTableWidgetItem(intToHex(static_cast<int>(data[i * 16 + j]), 0)));

                if (data[i * 16 + j] > 31 && data[i * 16 + j] < 127)
                {
                    textView.push_back(static_cast<char>(data[i * 16 + j]));
                }
                else
                {
                    textView.push_back('.');
                }
            }
            else
            {
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, j, new QTableWidgetItem(intToHex(0, 0)));
                textView.push_back('.');
            }
        }

        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 16, new QTableWidgetItem(textView));
        vLabels.append(intToHex(i));
    }

    ui->tableWidget->setVerticalHeaderLabels(vLabels);
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

    std::stringstream ss;
    ss << std::hex << num;
    auto tmp = ss.str();

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
            res.push_back(tmp[i]);
        }
    }

    return res;
}
