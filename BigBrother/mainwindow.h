#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include "lindeviceswidges.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QTableWidget* getTable();
    LinDevicesWidges *wid;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

