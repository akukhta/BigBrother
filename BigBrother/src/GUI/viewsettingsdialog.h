#ifndef VIEWSETTINGSDIALOG_H
#define VIEWSETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "Common/ViewSettings.h"

namespace Ui {
class ViewSettingsDialog;
}

class ViewSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewSettingsDialog(QWidget *parent = nullptr);
    ~ViewSettingsDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewSettingsDialog *ui;
    static QStringList const settings, values;
    static size_t const columnsCount;
};

#endif // VIEWSETTINGSDIALOG_H
