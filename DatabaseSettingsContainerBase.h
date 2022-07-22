#ifndef DATABASESETTINGSCONTAINERBASE_H
#define DATABASESETTINGSCONTAINERBASE_H

#include "DatabaseSettingsBase.h"

class DatabaseSettingsContainerBase
{
public:
    DatabaseSettingsContainerBase() = delete;
    
    static const std::shared_ptr<DatabaseSettingsBase>& getSettings();
    
protected:
    static std::shared_ptr<DatabaseSettingsBase> m_dbSettings;
};

#endif // DATABASESETTINGSCONTAINERBASE_H
