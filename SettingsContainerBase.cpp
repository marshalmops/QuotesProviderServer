#include "SettingsContainerBase.h"

std::shared_ptr<DatabaseSettingsBase> SettingsContainerBase::m_dbSettings   = std::shared_ptr<DatabaseSettingsBase>();
std::shared_ptr<CoreSettingsBase>     SettingsContainerBase::m_coreSettings = std::shared_ptr<CoreSettingsBase>();

const std::shared_ptr<DatabaseSettingsBase> &SettingsContainerBase::getDatabaseSettings()
{
    return m_dbSettings;
}

const std::shared_ptr<CoreSettingsBase> &SettingsContainerBase::getCoreSettings()
{
    return m_coreSettings;
}
