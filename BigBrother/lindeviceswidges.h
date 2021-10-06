#pragma once
#include <QWidget>
#include <QListWidgetItem>
#include <unordered_map>
#include "linuxdevicesmanager.h"
#include "networklistener.h"

namespace Ui {
class LinDevicesWidges;
}

class LinDevicesWidges : public QWidget
{
    Q_OBJECT

private:
    using callbackFunction = std::function<void (std::vector<NetworkDevice>)>;

public:
    explicit LinDevicesWidges(QWidget *parent = nullptr);
    void addCallback(callbackFunction callback);
    ~LinDevicesWidges();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LinDevicesWidges *ui;
    std::unordered_map<QListWidgetItem*, NetworkDevice> devicesTable;
    std::vector<NetworkDevice> devices;
    callbackFunction callback;
};
