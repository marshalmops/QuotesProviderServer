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
    
    return SettingsContainerEditable::setDatabaseSettings(std::move(databaseSettingsBase));
}

bool DatabaseLayerCreator::createDatabaseFacade(const QString &connectionName,
                                                std::unique_ptr<DatabaseFacadeBase> &databaseFacade)
{
    if (connectionName.isEmpty()) return false;
    
    auto settings = SettingsContainerBase::getDatabaseSettings();
    
    if (!settings->isValid()) return false;
    
    switch (settings->getDatabaseType()) {
    case DatabaseContext::DatabaseType::DT_SQLITE: {
        std::unique_ptr queryParser{std::make_unique<DatabaseQueryParserStandard>()};
        
        std::unique_ptr driver         {std::make_unique<DatabaseDriverSQLite>(connectionName, std::move(queryParser))};
        std::unique_ptr entityProcessor{std::make_unique<DatabaseEntityProcessorSQL>()};
        
        databaseFacade = std::make_unique<DatabaseFacadeStandard>(std::move(driver), std::move(entityProcessor));
    
        break;
    }
    default: return false;
    }
    
    return true;
}
