#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "GUI/mainwindow.h"
#include "Common/analyzer.h"
#include "Net/networklistenerfactory.h"
#include "Linux/linuxdevicesmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::unique_ptr<MainWindow> window;
    std::shared_ptr<PacketTable> table;
    std::unique_ptr<PacketHandler> handler;
    std::shared_ptr<Terminal> terminal;

    try
    {
        //terminal = std::make_shared<Terminal>();
        window = std::make_unique<MainWindow>(terminal);
        table = std::make_shared<PacketTable>(window->getTable());
        handler = std::make_unique<PacketHandler>(table->getPrintFunction());
    }

    catch(std::runtime_error const &err)
    {
        QMessageBox box;
        box.setWindowTitle("Error");
        box.setText(err.what());
        box.exec();
        return -1;
    }

//    std::cout << "Header2: " << sizeof(EnthernetIIHeader) << std::endl;
//    std::cout << "Align2: " << alignof(EnthernetIIHeader) << std::endl;
//    std::cout << "Header: " << sizeof(EthernetHeader) << std::endl;
//    std::cout << "IPv4 size:" << sizeof(IPv4Header) - sizeof(ProtocolHeader) << std::endl;
//    std::cout << "TCP size:" << sizeof(TCPHeader) - sizeof(TransportHeader) << std::endl;
//    std::cout << "UDP size:" << sizeof(UDPHeader) - sizeof(TransportHeader) << std::endl;

    Analyzer analyzer(std::move(window), table, std::move(handler));
    return a.exec();
}
