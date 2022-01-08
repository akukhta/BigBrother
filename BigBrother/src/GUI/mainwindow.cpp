#include "mainwindow.h"
#include <QMessageBox>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wid = new LinDevicesWidges();
    auto _layout = new QVBoxLayout();
    wid->setFixedSize(200, 150);
    _layout->addWidget(wid);
    PacketViewer *viewer = new PacketViewer();
    printerFunction = std::bind(&PacketViewer::printPacket, viewer, std::placeholders::_1);
    _layout->addWidget(viewer);
    ui->frame->setLayout(_layout);
    viewSettingDialog = std::make_unique<ViewSettingsDialog>();
    memoryDialog = std::make_unique<MemoryUsageDialog>();
}

QTableWidget* MainWindow::getTable()
{
    return ui->tableWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTableCallback(std::function<void (size_t)> callback)
{
    tableCallback = callback;
}

std::function<void (const std::string &)> MainWindow::getPrintFunction()
{
    return printerFunction;
}


void MainWindow::on_actionView_settings_triggered()
{
    viewSettingDialog->exec();
}


void MainWindow::on_actionMemory_usage_triggered()
{
    memoryDialog->exec();
}


void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    auto r = index.row();
    r++;
    tableCallback(index.row());
}

