#include <cstdint>
#include <bit>
#include "TransportHeader.h"


class TCPHeader final : public TransportHeader
{
public:
    virtual void print() override final {;};
private:
    std::uint16_t sourcePort;
    std::uint16_t destinationPort;
    std::uint32_t sequenceNumber;
    std::uint32_t ackNumber;

#if defined (__ORDER_BIG_ENDIAN__)
    std::uint16_t headerLength : 4;
    std::uint16_t reservedBits : 6;
    std::uint16_t urg : 1;
    std::uint16_t ack : 1;
    std::uint16_t psh : 1;
    std::uint16_t rst : 1;
    std::uint16_t syn : 1;
    std::uint16_t fin : 1;
#elif defined ()
    std::uint16_t fin : 1;
    //TODO: Implement TCP and UDP Headers and continue work on the project
#endif
};
