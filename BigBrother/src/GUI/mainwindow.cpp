#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<Terminal> terminal, QWidget *parent)
    : terminal(terminal), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wid = new LinDevicesWidges();
    pChooserWidget = new PrinterChooserWidget();
    auto _layout = new QVBoxLayout();
    _layout->addWidget(wid);
    _layout->addWidget(pChooserWidget);
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

