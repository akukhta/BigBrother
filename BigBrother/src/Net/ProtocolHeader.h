#pragma once

#pragma pack(push, 1)

class ProtocolHeader{
public:
    virtual std::string getInfo() = 0;
    virtual std::string getProtocolType() = 0;
    virtual std::string getSourceIP() = 0;
    virtual std::string getDestIP() = 0;
};

#pragma pack(pop)
