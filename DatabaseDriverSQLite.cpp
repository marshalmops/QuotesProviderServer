#include "DatabaseDriverSQLite.h"

DatabaseDriverSQLite::DatabaseDriverSQLite(const QString &connectionName,
                                           std::unique_ptr<DatabaseQueryParserStandard> &&queryParser)
    : DatabaseDriverStandard{connectionName, std::move(queryParser)}
{
    
}

bool DatabaseDriverSQLite::initializeConnection()
{
    auto dbSettings = SettingsContainerBase::getDatabaseSettings();
    
    QSqlDatabase db = QSqlDatabase::addDatabase(C_DATABASE_SQLITE_TYPE_STRING, m_connectionName);
    
    db.setDatabaseName(dbSettings->getDatabaseUrl().fileName());
    
    return db.open();
}

bool DatabaseDriverSQLite::executeQuery(const std::unique_ptr<DatabaseQueryBase> &query, 
                                        std::vector<std::shared_ptr<DatabaseQueryResultBase>> &results)
{
    if (!query->isValid()) return false;
    
    std::unique_ptr<DatabaseQueryParserResultInterface> parsedQuery{};
    
    if (!m_queryParser->parseQuery(query, parsedQuery))
        return false;
    
    DatabaseQueryParserResultSQL *parsedQuerySQL = dynamic_cast<DatabaseQueryParserResultSQL*>(parsedQuery.get());
    
    if (!parsedQuery.get()) return false;
    
    QString parsedQueryString{parsedQuerySQL->getSqlString()};
    
    if (parsedQueryString.isEmpty()) return false;
    
    return (executeRawQuery(parsedQueryString, results));
}
