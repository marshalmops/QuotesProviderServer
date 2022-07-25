#include "DatabaseDriverSQLite.h"

DatabaseDriverSQLite::DatabaseDriverSQLite(const QString &connectionName,
                                           std::unique_ptr<DatabaseQueryParserStandard> &&queryParser)
    : DatabaseDriverStandard{connectionName, std::move(queryParser)}
{
    
}

bool DatabaseDriverSQLite::initializeConnection()
{
    auto dbSettings = SettingsContainerBase::getSettings();
    
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
    
    QSqlDatabase db       {QSqlDatabase::database(m_connectionName)};
    QSqlQuery    rawResult{db.exec(parsedQueryString)};
    
    if (rawResult.lastError().isValid()) return false;
    
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> resultsBuffer{};
    
    while (rawResult.next()) {
        if (!rawResult.isValid()) return false;
        
        resultsBuffer.push_back(std::make_shared<DatabaseQueryResultStandard>(rawResult));
    }
    
    results = std::move(resultsBuffer);
    
    return true;
}
