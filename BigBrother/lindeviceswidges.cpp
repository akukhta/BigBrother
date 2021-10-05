#include "lindeviceswidges.h"
#include "ui_lindeviceswidges.h"

LinDevicesWidges::LinDevicesWidges(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinDevicesWidges)
{
    ui->setupUi(this);
    ui->listWidget->setFixedSize(this->size());
    auto devices = LinuxDevicesManager::getDevices();

    for (auto &device : devices)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(device.name), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Unchecked); // AND initialize check state
    }
}

LinDevicesWidges::~LinDevicesWidges()
{
    delete ui;
}
