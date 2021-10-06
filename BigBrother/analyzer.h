#pragma once

#include <thread>
#include "mainwindow.h"
#include "networklistener.h"

class Analyzer
{
public:
    Analyzer(std::unique_ptr<MainWindow> window, std::shared_ptr<PacketTable> const &table);

private:
    std::unique_ptr<MainWindow> window;
    std::shared_ptr<PacketTable> table;
    std::unique_ptr<NetworkListener> listener;
    std::thread listeningThread;
};

