#include "terminal.h"
#include "ui_terminal.h"

Terminal::Terminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Terminal)
{
    ui->setupUi(this);
    ui->textBrowser->setTextColor(Qt::white);
    ui->textBrowser->append("Big brother\n");
    out.open("out.txt");
}

Terminal::~Terminal()
{
    out.close();
    delete ui;
}

void Terminal::printMessage(std::string const &str)
{
    out << getTime().toStdString() << str << std::endl;
    //ui->textBrowser->append(getTime() + QString::fromStdString(str) + '\n');
}

void Terminal::printMessage(unsigned char *str, size_t size)
{
    std::string _str(reinterpret_cast<char*>(str), size);
    ui->textBrowser->append(getTime() + QString::fromStdString(_str) + '\n');
}

QString Terminal::getTime()
{
    return QTime::currentTime().toString() + ':';
}
