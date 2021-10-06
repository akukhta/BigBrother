#pragma once
#include <QWidget>
#include <QListWidgetItem>
#include <unordered_map>
#include "linuxdevicesmanager.h"

//Widget panel to get devices to catch
namespace Ui {
class LinDevicesWidges;
}

class LinDevicesWidges : public QWidget
{
    Q_OBJECT

private:
    using callbackFunction = std::function<void(std::vector<NetworkDevice>)>;
    using stopCallbackFunction = std::function<void()>;
public:
    explicit LinDevicesWidges(QWidget *parent = nullptr);
    ~LinDevicesWidges();
    std::unordered_map<QListWidgetItem*, NetworkDevice> devicesTable;
    void addCallbackFunction(callbackFunction func);
    void addStopCallbackFunction(stopCallbackFunction func);


private slots:
    void on_pushButton_clicked();

private:
    Ui::LinDevicesWidges *ui;
    callbackFunction func;
    stopCallbackFunction stopFunc;
    bool isRunning = false;
    QString const startListeningMsg = "Start listening", stopListeningMsg = "Stop listening";
};
