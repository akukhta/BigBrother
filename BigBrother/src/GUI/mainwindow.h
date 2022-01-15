#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QCloseEvent>
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
    void setTableCallback(std::function<void(size_t)> callback);
    void setExitCallback(std::function<void (void)> callback);
    void setClearTableCallback(std::function<void (void)> callback);
    std::function<void(std::string const&, std::vector<unsigned char> const &)> getPrintFunction();


private slots:
    void on_actionView_settings_triggered();

    void on_actionMemory_usage_triggered();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ViewSettingsDialog> viewSettingDialog;
    std::unique_ptr<MemoryUsageDialog> memoryDialog;
    std::function<void (size_t)> tableCallback;
    std::function<void (std::string const&, std::vector<unsigned char> const &)> printerFunction;
    std::function<void (void)> exitCallback;
    std::function<void (void)> clearTableCallback;
    void closeEvent(QCloseEvent *event);
};

