#ifndef MEMORYUSAGEDIALOG_H
#define MEMORYUSAGEDIALOG_H

#include <QDialog>
#include <QRegularExpressionValidator>
#include "Common/ViewSettings.h"

namespace Ui {
class MemoryUsageDialog;
}

class MemoryUsageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryUsageDialog(QWidget *parent = nullptr);
    ~MemoryUsageDialog();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    friend class Settings;
    Ui::MemoryUsageDialog *ui;
    static QStringList const sizeTypes;
    bool isDefaultSetting = true;
};

#endif // MEMORYUSAGEDIALOG_H
