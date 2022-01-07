#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include "lindeviceswidges.h"
#include "viewsettingsdialog.h"
#include "packetviewer.h"
#include "memoryusagedialog.h"

//Main UI class
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QTableWidget* getTable();
    ~MainWindow();
    LinDevicesWidges *wid;


private slots:
    void on_actionView_settings_triggered();

    void on_actionMemory_usage_triggered();

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ViewSettingsDialog> viewSettingDialog;
    std::unique_ptr<MemoryUsageDialog> memoryDialog;
};

