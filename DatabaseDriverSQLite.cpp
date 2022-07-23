#include "DatabaseDriverSQLite.h"

DatabaseDriverSQLite::DatabaseDriverSQLite(const QString &connectionName,
                                           std::unique_ptr<DatabaseQueryParserStandard> &&queryParser)
    : DatabaseDriverStandard{connectionName, std::move(queryParser)}
{
    auto dbSettings = DatabaseSettingsContainerBase::getSettings();
    
    QSqlDatabase db = QSqlDatabase::addDatabase(C_DATABASE_SQLITE_TYPE_STRING, connectionName);
    
    db.setDatabaseName(dbSettings->getDatabaseUrl().fileName());
}

bool DatabaseDriverSQLite::executeQuery(const std::unique_ptr<DatabaseQueryBase> &query, 
                                        std::vector<DatabaseQueryResultBase> &results)
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
    
    std::vector<DatabaseQueryResultBase> resultsBuffer{};
    
    while (rawResult.next()) {
        if (!rawResult.isValid()) return false;
        
        resultsBuffer.push_back(DatabaseQueryResultStandard{rawResult});
    }
    
    results = std::move(resultsBuffer);
    
    return true;
}
