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
    std::vector<NetworkListener>listeners;
    std::thread listeningThread;
    std::vector<NetworkDevice> selectedDevices;
    void startListening(std::vector<NetworkDevice> selectedDevices);
    void getSelectedDevices(std::vector<NetworkDevice> selectedDevices);
};

