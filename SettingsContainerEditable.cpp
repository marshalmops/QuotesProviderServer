#include "SettingsContainerEditable.h"

bool SettingsContainerEditable::setDatabaseSettings(std::unique_ptr<DatabaseSettingsBase> &&dbSettings)
{
    if (!dbSettings->isValid()) return false;
    
    m_dbSettings.reset(dbSettings.release());
    
    return true;
}

bool SettingsContainerEditable::setCoreSettings(std::unique_ptr<CoreSettingsBase> &&coreSettings)
{
    if (!coreSettings->isValid()) return false;
    
    m_coreSettings.reset(coreSettings.release());
    
    return true;
}
