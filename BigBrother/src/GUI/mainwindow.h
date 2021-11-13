#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include "lindeviceswidges.h"
#include "printerchooserwidget.h"
#include "terminal.h"

//Main UI class
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<Terminal> terminal, QWidget *parent = nullptr);
    QTableWidget* getTable();
    ~MainWindow();
    LinDevicesWidges *wid;
    PrinterChooserWidget *pChooserWidget;

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Terminal> terminal;
};

