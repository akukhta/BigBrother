#include "mainwindow.h"
#include <QMessageBox>
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
    viewSettingDialog = std::make_unique<ViewSettingsDialog>();
}

QTableWidget* MainWindow::getTable()
{
    return ui->tableWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionView_settings_triggered()
{
    viewSettingDialog->exec();
}

