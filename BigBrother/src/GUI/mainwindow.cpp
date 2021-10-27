#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wid = new LinDevicesWidges();
    pChooserWidget = new PrinterChooserWidget();
    terminalWidget = new Terminal();
    auto _layout = new QVBoxLayout();
    _layout->addWidget(wid);
    _layout->addWidget(pChooserWidget);
    _layout->addWidget(terminalWidget);
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

