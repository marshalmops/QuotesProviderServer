#include "DatabaseSettingsContainerBase.h"

std::shared_ptr<DatabaseSettingsBase> DatabaseSettingsBase::m_dbSettings = std::shared_ptr<DatabaseSettingsBase>();

const std::shared_ptr<DatabaseSettingsBase> &DatabaseSettingsContainerBase::getSettings()
{
    return m_dbSettings;
}
