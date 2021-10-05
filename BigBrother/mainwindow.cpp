#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->gridLayout->addWidget(new LinDevicesWidges(),1,2);
    auto _layout = new QVBoxLayout();
    _layout->addWidget(new LinDevicesWidges());
    ui->frame->setLayout(_layout);

}

QTableWidget* MainWindow::getTable()
{
    return ui->tableWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}

