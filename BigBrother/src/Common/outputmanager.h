#pragma once
#include <memory>

class OutputManager : std::enable_shared_from_this<OutputManager>
{
public:
    static std::shared_ptr<OutputManager> getInstance();
    static std::shared_ptr<OutputManager> manager;
};
