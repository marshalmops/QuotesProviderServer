#include "FilesProcessorSettings.h"

bool FilesProcessorSettings::saveSettings()
{
    return (saveSettingsWithFileName(DatabaseSettingsBase::C_DEFAULT_DATABASE_SETTINGS_FILENAME, SettingsContainerBase::getDatabaseSettings())
         && saveSettingsWithFileName(CoreSettingsBase::C_DEFAULT_CORE_SETTINGS_FILENAME,         SettingsContainerBase::getCoreSettings()));
}

bool FilesProcessorSettings::loadSettings()
{
    QJsonObject coreSettingsJson{},
                dbSettingsJson  {};
                
    if (!loadSettingsContentWithFileName(CoreSettingsBase::C_DEFAULT_CORE_SETTINGS_FILENAME, coreSettingsJson)
     || !loadSettingsContentWithFileName(DatabaseSettingsBase::C_DEFAULT_DATABASE_SETTINGS_FILENAME, dbSettingsJson))
    {
        return false;
    }
    
    std::unique_ptr coreSettingsBase = std::make_unique<CoreSettingsBase>();
    
    if (!coreSettingsBase->fromJson(coreSettingsJson))
        return false;
    
    if (!SettingsContainerEditable::setCoreSettings(std::move(coreSettingsBase)))
        return false;
    
    std::unique_ptr databaseSettingsBase = std::make_unique<DatabaseSettingsBase>();
    
    if (!databaseSettingsBase->fromJson(dbSettingsJson)) 
        return false;
    if (!DatabaseLayerCreator::createDatabaseSettingsUsingBase(std::move(databaseSettingsBase)))
        return false;
    
    return true;
}

bool FilesProcessorSettings::saveSettingsWithFileName(const QString &filename,
                                                      const std::shared_ptr<SettingsInterface> &settingsToSave)
{
    if (filename.isEmpty()) return false;
    
    QFile settingsFile{filename};
    
    if (!settingsFile.open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Truncate))
        return false;
    
    QJsonObject jsonToSaveRoot{};
    
    if (!settingsToSave->toJson(jsonToSaveRoot)) return false;
    
    auto jsonBytes = QJsonDocument{jsonToSaveRoot}.toJson();
    
    if (jsonBytes.isEmpty()) return false;
    
    return (settingsFile.write(jsonBytes) == jsonBytes.length());
}

bool FilesProcessorSettings::loadSettingsContentWithFileName(const QString &filename,
                                                             QJsonObject &settingsJson)
{
    QFile settingsFile{filename};
    
    if (!settingsFile.open(QFile::OpenModeFlag::ReadOnly))
        return false;
    
    auto jsonBytes = settingsFile.readAll();
    
    QJsonObject jsonRoot{QJsonDocument::fromJson(jsonBytes).object()};
    
    if (jsonRoot.isEmpty()) return false;
    
    settingsJson = std::move(jsonRoot);
    
    return true;
}
