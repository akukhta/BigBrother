#pragma once

#include <memory>
#include <QSettings>
#include <filesystem>
#include "GUI/viewsettingsdialog.h"
#include "GUI/memoryusagedialog.h"

class Settings : public std::enable_shared_from_this<Settings>
{
public:
    std::shared_ptr<Settings> static getInstance()
    {
        static std::shared_ptr<Settings> instance(new Settings());
        return instance;
    }

    enum class viewType : bool { HEX, DEC };

    viewType getMacType();
    viewType getIPType();

    size_t getMaxDumpSize();
    size_t getSizeType();

    ~Settings();

private:
    friend class ViewSettingsDialog;
    friend class MemoryUsageDialog;

    static std::string const settingsFilePath;
    static QStringList const tags;

    Settings();

    std::unique_ptr<QSettings> sttngs;

    void setMacType(viewType type);
    void setIPType(viewType type);

    void setMaxDumpSize(size_t size);
    void setSizeType(size_t type);
};
