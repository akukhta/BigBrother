#include "memoryusagedialog.h"
#include "ui_memoryusagedialog.h"

QStringList const MemoryUsageDialog::sizeTypes = {"b", "kb", "mb", "gb"};

MemoryUsageDialog::MemoryUsageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemoryUsageDialog)
{
    auto settings = Settings::getInstance();
    ui->setupUi(this);
    ui->comboBox->addItems(sizeTypes);
    ui->lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*"), ui->lineEdit));
    ui->lineEdit->setText(QString::number(settings->getMaxDumpSize()));
    ui->comboBox->setCurrentText(sizeTypes[settings->getSizeType()]);
}

MemoryUsageDialog::~MemoryUsageDialog()
{
    delete ui;
}

void MemoryUsageDialog::on_pushButton_clicked()
{
    close();
}


void MemoryUsageDialog::on_lineEdit_textChanged(const QString &arg1)
{
    Settings::getInstance()->setMaxDumpSize(arg1.toUInt());
}

void MemoryUsageDialog::on_comboBox_currentIndexChanged(int index)
{
    if (!isDefaultSetting)
    {
        Settings::getInstance()->setSizeType(static_cast<size_t>(index));
    }
    else
    {
        isDefaultSetting = false;
    }
}


void MemoryUsageDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ;
}

