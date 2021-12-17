#pragma once

#include <memory>
#include "GUI/viewsettingsdialog.h"

class ViewSettings : public std::enable_shared_from_this<ViewSettings>
{
public:
    std::shared_ptr<ViewSettings> getInstance()
    {
        static std::shared_ptr<ViewSettings> instance(new ViewSettings());
        return instance;
    }

    enum class viewType : bool { HEX, DEC };

private:
    friend class ViewSettingsDialog;

    ViewSettings() = default;

    viewType mac, ip;

    viewType getMacType()
    {
        return mac;
    }

    viewType getIPType()
    {
        return ip;
    }

    void setMacType(viewType type)
    {
        mac = type;
    }

    void setIPType(viewType type)
    {
        ip = type;
    }
};
