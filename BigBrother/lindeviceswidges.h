#pragma once
#include <QWidget>
#include "linuxdevicesmanager.h"

namespace Ui {
class LinDevicesWidges;
}

class LinDevicesWidges : public QWidget
{
    Q_OBJECT

public:
    explicit LinDevicesWidges(QWidget *parent = nullptr);
    ~LinDevicesWidges();

private:
    Ui::LinDevicesWidges *ui;
};
