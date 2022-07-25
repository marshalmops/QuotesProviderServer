#include "SettingsContainerEditable.h"

bool SettingsContainerEditable::setDatabaseSettings(std::unique_ptr<DatabaseSettingsBase> &&dbSettings)
{
    if (!dbSettings->isValid()) return false;
    
    m_dbSettings = std::shared_ptr<DatabaseSettingsBase>{dbSettings.release()};
    
    return true;
}

bool SettingsContainerEditable::setCoreSettings(std::unique_ptr<CoreSettingsBase> &&coreSettings)
{
    if (!coreSettings->isValid()) return false;
    
    m_coreSettings = std::shared_ptr<CoreSettingsBase>{coreSettings.release()};
    
    return true;
}
