#include "FilesProcessorSettings.h"

FilesProcessorSettings::FilesProcessorSettings()
{
    
}

bool FilesProcessorSettings::saveSettings()
{
    QFile dbSettingsFile{DatabaseSettingsBase::C_DEFAULT_DATABASE_SETTINGS_FILENAME};
    
    if (!dbSettingsFile.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate))
        return false;
    
    auto settings = DatabaseSettingsContainerBase::getSettings();
    
    QJsonObject jsonToSaveRoot{};
    
    if (!settings->toJson(jsonToSaveRoot)) return false;
    
    auto jsonBytes = QJsonDocument{jsonToSaveRoot}.toJson();
    
    if (jsonBytes.isEmpty()) return false;
    
    return (dbSettingsFile.write(jsonBytes) == jsonBytes.length());
}

bool FilesProcessorSettings::loadSettings()
{
    QFile dbSettingsFile{DatabaseSettingsBase::C_DEFAULT_DATABASE_SETTINGS_FILENAME};
    
    if (!dbSettingsFile.open(QFile::OpenModeFlag::ReadOnly))
        return false;
    
    auto jsonBytes = dbSettingsFile.readAll();
    
    QJsonObject jsonRoot{QJsonDocument::fromJson(jsonBytes).object()};
    
    if (jsonRoot.isEmpty()) return false;
    
    std::unique_ptr settingsBase = std::make_unique<DatabaseSettingsBase>();
    
    if (!settingsBase->fromJson(jsonRoot)) return false;
    
    return DatabaseLayerCreator::createDatabaseSettingsUsingBase(std::move(settingsBase));
}
