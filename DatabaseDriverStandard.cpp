#include "DatabaseDriverStandard.h"

DatabaseDriverStandard::DatabaseDriverStandard(const QString &connectionName,
                                               std::unique_ptr<DatabaseQueryParserStandard> &&queryParser)
    : DatabaseDriverBase{std::unique_ptr<DatabaseQueryParserInterface>(queryParser.release())},
      m_connectionName{connectionName}
{
    
}

DatabaseDriverStandard::~DatabaseDriverStandard()
{
    if (!m_connectionName.isEmpty() && QSqlDatabase::contains(m_connectionName))
        QSqlDatabase::removeDatabase(m_connectionName);
}

bool DatabaseDriverStandard::executeRawQuery(const QString &rawQuery, 
                                             std::vector<std::shared_ptr<DatabaseQueryResultBase> > &results)
{
    QSqlDatabase db       {QSqlDatabase::database(m_connectionName)};
    QSqlQuery    rawResult{db.exec(rawQuery)};

    if (rawResult.lastError().type() != QSqlError::NoError)
        return false;
    
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> resultsBuffer{};
    
    while (rawResult.next()) {
        if (!rawResult.isValid()) return false;
        
        resultsBuffer.push_back(std::make_shared<DatabaseQueryResultStandard>(rawResult.record()));
    }
    
    results = std::move(resultsBuffer);
    
//    auto i1 = rawResult.record().value(0);
//    auto i2 = rawResult.record().value(1);
//    auto i3 = rawResult.record().value(2);
    
    return true;
}

bool DatabaseDriverStandard::checkTablesOnExisting(const QStringList &tablesToCheck)
{
    QSqlDatabase db{QSqlDatabase::database(m_connectionName)};
    
    auto gottenTables = db.tables();
    
    foreach (const auto& curTable, tablesToCheck) {
        if (!gottenTables.contains(curTable))
            return false;
    }
    
    return true;
}
