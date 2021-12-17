#include "packetviewer.h"
#include "ui_packetviewer.h"

PacketViewer::PacketViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PacketViewer)
{
    ui->setupUi(this);
}

PacketViewer::~PacketViewer()
{
    delete ui;
}
