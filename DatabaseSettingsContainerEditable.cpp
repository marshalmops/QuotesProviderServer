#include "DatabaseSettingsContainerEditable.h"

bool DatabaseSettingsContainerEditable::setSettings(std::unique_ptr<DatabaseSettingsBase> &&settings)
{
    if (!) return false;
    
    m_dbSettings = std::shared_ptr<DatabaseSettingsBase>{settings.release()};
    
    return true;
}
