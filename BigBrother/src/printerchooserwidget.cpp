#include "printerchooserwidget.h"
#include "ui_printerchooserwidget.h"

PrinterChooserWidget::PrinterChooserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterChooserWidget)
{
    ui->setupUi(this);
}

PrinterChooserWidget::~PrinterChooserWidget()
{
    delete ui;
}
