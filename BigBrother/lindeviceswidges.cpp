#include "lindeviceswidges.h"
#include "ui_lindeviceswidges.h"

LinDevicesWidges::LinDevicesWidges(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinDevicesWidges)
{
    ui->setupUi(this);
    ui->listWidget->setFixedSize(this->size());
    devices = LinuxDevicesManager::getDevices();

    for (auto &device : devices)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(device.name), ui->listWidget);
        devicesTable.insert(std::make_pair(item, device));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Unchecked); // AND initialize check state
    }
}

void LinDevicesWidges::addCallback(callbackFunction callback)
{
    this->callback = callback;
}

LinDevicesWidges::~LinDevicesWidges()
{
    delete ui;
}

void LinDevicesWidges::on_pushButton_clicked()
{
    std::vector<NetworkDevice> devices;

    for (size_t i = 0; i < ui->listWidget->count(); i++)
    {
        if (ui->listWidget->item(i)->checkState() == Qt::Checked)
        {
            devices.push_back(devicesTable[ui->listWidget->item(i)]);
        }
    }
}

