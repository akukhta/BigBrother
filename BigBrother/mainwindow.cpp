#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->formLayout->addRow(new LinDevicesWidges());
}

QTableWidget* MainWindow::getTable()
{
    return ui->tableWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}

