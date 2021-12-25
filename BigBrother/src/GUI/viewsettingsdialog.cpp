#include "viewsettingsdialog.h"
#include "ui_viewsettingsdialog.h"

QStringList const ViewSettingsDialog::settings{"MAC", "IP"};
QStringList const ViewSettingsDialog::values{"hex", "dec"};
size_t const ViewSettingsDialog::columnsCount = 2;

ViewSettingsDialog::ViewSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewSettingsDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(columnsCount);
    auto _settings = Settings::getInstance();

    for (size_t i = 0; i < settings.length(); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(settings[i]));
        ui->tableWidget->setCellWidget(i, 1, new QComboBox);
        static_cast<QComboBox *>(ui->tableWidget->cellWidget(i, 1))->addItems(values);
    }

    static_cast<QComboBox *>(ui->tableWidget->cellWidget(0, 1))->setCurrentIndex(_settings->getMacType() == Settings::viewType::HEX ? 0 : 1);
    static_cast<QComboBox *>(ui->tableWidget->cellWidget(1, 1))->setCurrentIndex(_settings->getIPType() == Settings::viewType::HEX ? 0 : 1);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ViewSettingsDialog::~ViewSettingsDialog()
{
    delete ui;
}

void ViewSettingsDialog::on_pushButton_clicked()
{
    auto settings = Settings::getInstance();
    settings->setMacType(static_cast<QComboBox *>(ui->tableWidget->cellWidget(0, 1))->currentIndex() == 0 ? Settings::viewType::HEX : Settings::viewType::DEC);
    settings->setIPType(static_cast<QComboBox *>(ui->tableWidget->cellWidget(1, 1))->currentIndex() == 0 ? Settings::viewType::HEX : Settings::viewType::DEC);
    close();
}

