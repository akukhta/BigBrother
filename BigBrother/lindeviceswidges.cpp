#include "lindeviceswidges.h"
#include "ui_lindeviceswidges.h"

LinDevicesWidges::LinDevicesWidges(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinDevicesWidges)
{
    ui->setupUi(this);
    ui->listWidget->setFixedSize(this->size());
}

LinDevicesWidges::~LinDevicesWidges()
{
    delete ui;
}
