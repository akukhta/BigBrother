#include <iostream>
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
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        devicesTable.insert(std::make_pair(item, device));
    }
}

LinDevicesWidges::~LinDevicesWidges()
{
    delete ui;
}

void LinDevicesWidges::addCallbackFunction(callbackFunction func)
{
    this->func = func;
}

void LinDevicesWidges::addStopCallbackFunction(stopCallbackFunction func)
{
    this->stopFunc = func;
}

void LinDevicesWidges::on_pushButton_clicked()
{
    if (!isRunning)
    {
        std::vector<NetworkDevice> selectedDevices;

        for (size_t i = 0; i < ui->listWidget->count(); i++)
        {
            if (ui->listWidget->item(i)->checkState() == Qt::Checked)
            {
                selectedDevices.push_back(devicesTable.at(ui->listWidget->item(i)));
            }
        }

        func(selectedDevices);
        ui->pushButton->setText(stopListeningMsg);
        isRunning = true;
    }
    else
    {
        stopFunc();
        ui->pushButton->setText(startListeningMsg);
        isRunning = false;
    }
}

