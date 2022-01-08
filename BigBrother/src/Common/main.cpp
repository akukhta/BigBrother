#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <functional>
#include "GUI/mainwindow.h"
#include "Common/analyzer.h"
#include "Net/networklistenerfactory.h"
#include "Linux/linuxdevicesmanager.h"
#include "Common/packetsstorage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::unique_ptr<MainWindow> window;
    std::shared_ptr<PacketTable> table;
    std::unique_ptr<PacketHandler> handler;
    std::shared_ptr<PacketsStorage> storage;

    try
    {
        window = std::make_unique<MainWindow>();
        storage = std::make_shared<PacketsStorage>();
        table = std::make_shared<PacketTable>(window->getTable(), storage);
        table->setPrintFunction(window->getPrintFunction());
        window->setTableCallback(std::bind(&PacketTable::clicked, table, std::placeholders::_1));
        handler = std::make_unique<PacketHandler>(table->getPrintFunction(), storage);
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

    //std::cout << "Native size:" << sizeof(std::unique_ptr<EthernetHeader>) + sizeof(std::unique_ptr<ProtocolHeader>) + sizeof(std::unique_ptr<TransportHeader>)
    //             + sizeof(EnthernetIIHeader) + sizeof(TCPHeader) + sizeof(IPv4Header) << std::endl;

    Analyzer analyzer(std::move(window), table, std::move(handler), std::move(storage));
    return a.exec();
}
