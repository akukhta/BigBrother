#pragma once

#include <thread>
#include "Net/networklistener.h"
#include "Net/networklistenerfactory.h"
#include "GUI/mainwindow.h"
#include "Common/packethandler.h"
#include "Common/packetsstorage.h"

//Generic class
//Todo: make IP Header
class Analyzer
{
public:
    Analyzer(std::unique_ptr<MainWindow> window, std::shared_ptr<PacketTable> const &table, std::unique_ptr<PacketHandler> handler, std::shared_ptr<PacketsStorage> storage);

private:
    std::unique_ptr<MainWindow> window;
    std::shared_ptr<PacketTable> table;
    std::unique_ptr<PacketHandler> handler;
    std::shared_ptr<PacketsStorage> storage;
    std::vector<std::unique_ptr<NetworkListener>> listener;
    void startListening(std::unique_ptr<std::vector<NetworkDevice>>);
    void stopListening();
    std::function<void (std::vector<unsigned char>)> addingHandler = [this](std::vector<unsigned char> packet)
        {handler->addToQueue(packet);};

};

