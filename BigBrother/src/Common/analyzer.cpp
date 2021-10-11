#include "analyzer.h"
#include <iostream>

#ifdef __unix
    #include "Linux/networklistenerlin.h"
#endif


Analyzer::Analyzer(std::unique_ptr<MainWindow> window, std::shared_ptr<PacketTable> const &table, std::unique_ptr<PacketHandler> handler)
    : window(std::move(window)), table(std::move(table)), handler(std::move(handler))
{

    if (!this->window || !this->table)
    {
        throw std::runtime_error("Can not own UI objects!");
    }

    this->window->show();
    this->window->wid->addCallbackFunction
            ([this](std::unique_ptr<std::vector<NetworkDevice>> devices){startListening(std::move(devices));});
    this->window->wid->addStopCallbackFunction([this](){stopListening();});

    this->table->addRow("Hello World!");
    this->handler->startHandling();
}

void Analyzer::startListening(std::unique_ptr<std::vector<NetworkDevice>> selectedDevices)
{
    listener.clear();

    for (auto const & device : *selectedDevices)
    {
        listener.push_back(std::move(getListener(device, table, addingHandler)));
        std::thread([this](){listener.back()->ScanNetwork();}).detach();
    }
}

void Analyzer::stopListening()
{
    for (auto & _listener : listener)
    {
        _listener->StopScan();
    }
}
