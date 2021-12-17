#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include "lindeviceswidges.h"
#include "viewsettingsdialog.h"
#include "packetviewer.h"

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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ViewSettingsDialog> viewSettingDialog;
};

