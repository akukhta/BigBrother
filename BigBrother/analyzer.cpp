#include "analyzer.h"

Analyzer::Analyzer(std::unique_ptr<MainWindow> window, std::shared_ptr<PacketTable> const &table)
    : window(std::move(window)), table(std::move(table))
{

    if (!this->window || !this->table)
    {
        throw std::runtime_error("Can not own UI objects!");
    }

    this->window->show();
    this->table->addRow("Hello World!");
}

void Analyzer::startListening(std::vector<NetworkDevice> selectedDevices)
{
    getSelectedDevices(selectedDevices);
}

void Analyzer::getSelectedDevices(std::vector<NetworkDevice> selectedDevices)
{
    this->selectedDevices = selectedDevices;
}
