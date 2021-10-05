#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "mainwindow.h"
#include "analyzer.h"
#include "networklistenerfactory.h"
#include "linuxdevicesmanager.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

    std::unique_ptr<MainWindow> window;
    std::shared_ptr<PacketTable> table;
    std::unique_ptr<NetworkListener> listener;

    try
    {
        window = std::make_unique<MainWindow>();
        table = std::make_shared<PacketTable>(window->getTable());
    }

    catch(std::runtime_error const &err)
    {
        QMessageBox box;
        box.setWindowTitle("Error");
        box.setText(err.what());
        box.exec();
        return -1;
    }

    Analyzer analyzer(std::move(window), table);
    return a.exec();
}
