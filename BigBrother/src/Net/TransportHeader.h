#pragma once
#include <string>
#include <sstream>

#pragma pack (push, 1)

class TransportHeader
{
public:
    virtual void print() = 0;
    virtual std::string getTransportType() = 0;
    virtual std::string getSourcePort() = 0;
    virtual std::string getDestPort() = 0;
    virtual std::string getInfo() = 0;
};

#pragma pack (pop)
