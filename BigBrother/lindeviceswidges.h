#ifndef LINDEVICESWIDGES_H
#define LINDEVICESWIDGES_H

#include <QWidget>

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

#endif // LINDEVICESWIDGES_H
