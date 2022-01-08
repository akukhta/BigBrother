#include "packetviewer.h"
#include "ui_packetviewer.h"

PacketViewer::PacketViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PacketViewer)
{

    ui->setupUi(this);
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
