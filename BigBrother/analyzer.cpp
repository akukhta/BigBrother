#include "analyzer.h"
#include <iostream>

Analyzer::Analyzer(std::unique_ptr<MainWindow> window, std::shared_ptr<PacketTable> const &table, std::unique_ptr<NetworkListener> listener)
    : window(std::move(window)), table(std::move(table)), listener(std::move(listener))
{

    if (!this->window || !this->table)
    {
        throw std::runtime_error("Can not own UI objects!");
    }

    if (!this->listener)
    {
        throw std::runtime_error("Can not own network listener!");
    }

    this->window->show();
    this->table->addRow("Hello World!");
    this->listener->ScanNetwork();
}
