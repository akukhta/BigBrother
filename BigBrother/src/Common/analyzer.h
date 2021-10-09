#pragma once

#include <thread>
#include "Net/networklistener.h"
#include "Net/networklistenerfactory.h"
#include "GUI/mainwindow.h"

//Generic class
//Todo: make IP Header
class Analyzer
{
public:
    Analyzer(std::unique_ptr<MainWindow> window, std::shared_ptr<PacketTable> const &table);

private:
    std::unique_ptr<MainWindow> window;
    std::shared_ptr<PacketTable> table;
    std::vector<std::unique_ptr<NetworkListener>> listener;
    void startListening(std::unique_ptr<std::vector<NetworkDevice>>);
    void stopListening();

};

