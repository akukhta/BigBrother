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

    for (size_t i = 0; i < settings.length(); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(settings[i]));
        ui->tableWidget->setCellWidget(i, 1, new QComboBox);
        static_cast<QComboBox *>(ui->tableWidget->cellWidget(i, 1))->addItems(values);
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ViewSettingsDialog::~ViewSettingsDialog()
{
    delete ui;
}

void ViewSettingsDialog::on_pushButton_clicked()
{
    close();
}

