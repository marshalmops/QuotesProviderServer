#ifndef SETTINGSCONTAINERBASE_H
#define SETTINGSCONTAINERBASE_H

#include "DatabaseSettingsBase.h"
#include "CoreSettingsBase.h"

class SettingsContainerBase
{
public:
    SettingsContainerBase() = delete;
    
    static const std::shared_ptr<DatabaseSettingsBase>& getDatabaseSettings();
    static const std::shared_ptr<CoreSettingsBase>&     getCoreSettings();
    
protected:
    static std::shared_ptr<DatabaseSettingsBase> m_dbSettings;
    static std::shared_ptr<CoreSettingsBase>     m_coreSettings;
};

#endif // SETTINGSCONTAINERBASE_H
