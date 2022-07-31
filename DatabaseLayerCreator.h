#ifndef DATABASELAYERCREATOR_H
#define DATABASELAYERCREATOR_H

#include "SettingsContainerEditable.h"

#include "DatabaseSettingsSQLite.h"

#include "DatabaseFacadeStandard.h"

#include "DatabaseEntityProcessorSQL.h"

#include "DatabaseQueryParserStandard.h"

#include "DatabaseDriverSQLite.h"

class DatabaseLayerCreator
{
public:
    DatabaseLayerCreator() = delete;
    
    static bool createDatabaseSettingsUsingBase(std::unique_ptr<DatabaseSettingsBase> &&databaseSettingsBase);
    static bool createDatabaseFacade           (const QString &connectionName,
                                                std::unique_ptr<DatabaseFacadeBase> &databaseFacade);
    
private:
    static std::atomic_flag m_tablesInitializingFlag;
};

#endif // DATABASELAYERCREATOR_H
