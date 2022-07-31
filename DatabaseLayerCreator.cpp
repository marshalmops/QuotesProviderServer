#include "DatabaseLayerCreator.h"

std::atomic_flag DatabaseLayerCreator::m_tablesInitializingFlag = ATOMIC_FLAG_INIT;

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
        
        std::unique_ptr driver{std::make_unique<DatabaseDriverSQLite>(connectionName, std::move(queryParser))};
        
        if (!driver->initializeConnection()) return false;
        
        std::unique_ptr entityProcessor{std::make_unique<DatabaseEntityProcessorSQL>()};
        
        databaseFacade = std::make_unique<DatabaseFacadeStandard>(std::move(driver), std::move(entityProcessor));
    
        break;
    }
    default: return false;
    }
    
    if (!m_tablesInitializingFlag.test_and_set(std::memory_order_acq_rel)) {
        if (!databaseFacade->testDatabaseCorrectness()) {
            if (!databaseFacade->initializeTables())
                return false;
        }
        
        m_tablesInitializingFlag.clear(std::memory_order_release);
    }
    
    return true;
}
