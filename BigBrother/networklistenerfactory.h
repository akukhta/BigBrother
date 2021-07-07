#pragma once
#include "networklistener.h"
#include "networklistenerlin.h"
#include "networklistenerwin.h"

std::unique_ptr<NetworkListener> GetTargetListener(std::shared_ptr<PacketTable> const &table)
{
#ifdef __unix
    auto listener = std::make_unique<NetworkListenerLin>(table);
    return std::move(listener);
#endif

#ifdef __win32__
    auto listener = std::make_unique<NetworkListenerWin>(table);
    return std::move(listener);
#endif
}
