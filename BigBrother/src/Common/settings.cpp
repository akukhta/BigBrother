#include "Common/ViewSettings.h"

std::string const Settings::settingsFilePath = "settings.ini";
QStringList const Settings::tags = {"MACTYPE", "IPTYPE", "DUMBSIZE", "SIZEFORMAT"};

Settings::Settings()
{
    sttngs = nullptr;

    if (!std::filesystem::exists(settingsFilePath))
    {
        sttngs = std::make_unique<QSettings>(QString::fromStdString(settingsFilePath), QSettings::IniFormat);

        if (!sttngs->childGroups().contains("General"))
        {
            sttngs->setValue(tags[0], 0);
            sttngs->setValue(tags[1], 1);
            sttngs->setValue(tags[2], 500);
            sttngs->setValue(tags[3], 2);
            sttngs->sync();
        }
    }
    else
    {
        sttngs = std::make_unique<QSettings>(QString::fromStdString(settingsFilePath), QSettings::IniFormat);
    }
}

Settings::~Settings()
{
    sttngs->sync();
}

Settings::viewType Settings::getMacType()
{
    return sttngs->value(tags[0]).toBool() ? viewType::DEC : viewType::HEX;
}

Settings::viewType Settings::getIPType()
{
    return sttngs->value(tags[1]).toBool() ? viewType::DEC : viewType::HEX;
}

size_t Settings::getMaxDumpSize()
{
    return sttngs->value(tags[2]).toUInt();
}

size_t Settings::getSizeType()
{
    return sttngs->value(tags[3]).toUInt();
}

void Settings::setMacType(Settings::viewType type)
{
    sttngs->setValue(tags[0], type == viewType::DEC ? "1" : "0");
}

void Settings::setIPType(Settings::viewType type)
{
    sttngs->setValue(tags[1], type == viewType::DEC ? "1" : "0");
}

void Settings::setMaxDumpSize(size_t size)
{
    sttngs->setValue(tags[2], static_cast<unsigned int>(size));
}

void Settings::setSizeType(size_t type)
{
    sttngs->setValue(tags[3], static_cast<unsigned int>(type));
}
