#include "DatabaseLayerCreator.h"


bool DatabaseLayerCreator::createDatabaseSettingsUsingBase(std::unique_ptr<DatabaseSettingsBase> &&databaseSettingsBase)
{
    if (!databaseSettingsBase->isValid()) return false;
    
    switch (databaseSettingsBase->getDatabaseType()) {
    case DatabaseContext::DatabaseType::DT_SQLITE: {
        databaseSettingsBase = std::make_unique<DatabaseSettingsSQLite>(std::move(*databaseSettingsBase.release()));
    
        break;
    }
    default: return false;
    }
    
    return DatabaseSettingsContainerEditable::setSettings(std::move(databaseSettingsBase));
}
