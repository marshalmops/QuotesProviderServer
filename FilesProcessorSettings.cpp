#include "FilesProcessorSettings.h"

FilesProcessorSettings::FilesProcessorSettings()
{
    
}

bool FilesProcessorSettings::saveSettings()
{
    QFile dbSettingsFile{DatabaseSettingsBase::C_DEFAULT_DATABASE_SETTINGS_FILENAME};
    
    if (!dbSettingsFile.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate))
        return false;
    
    QJsonObject jsonToSaveRoot{};
    
    // reading type...
    
    return true;
}

bool FilesProcessorSettings::loadSettings()
{
    
}
