#include "mainwindow.h"
#include "analyzer.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<MainWindow> window;
    std::unique_ptr<PacketTable> table;
    std::unique_ptr<NetworkListener> listener;

    try
    {
        window = std::make_unique<MainWindow>();
        table = std::make_unique<PacketTable>(window->getTable());
        listener = std::make_unique<NetworkListener>();
    }

    catch(std::runtime_error const &err)
    {
        QMessageBox box;
        box.setWindowTitle("Error");
        box.setText(err.what());
        box.exec();
        return -1;
    }

    Analyzer analyzer(std::move(window), std::move(table), std::move(listener));
    return a.exec();
}
