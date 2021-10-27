#include "terminal.h"
#include "ui_terminal.h"

Terminal::Terminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Terminal)
{
    ui->setupUi(this);
    ui->textBrowser->setTextColor(Qt::white);
    ui->textBrowser->append("Big brother\n");
}

Terminal::~Terminal()
{
    delete ui;
}
