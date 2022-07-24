#ifndef DATABASEDRIVERSQLITE_H
#define DATABASEDRIVERSQLITE_H

#include "DatabaseDriverStandard.h"

#include "DatabaseQueryParserResultSQL.h"

class DatabaseDriverSQLite : public DatabaseDriverStandard
{
    constexpr static const char* C_DATABASE_SQLITE_TYPE_STRING = "QSQLITE";
public:
    DatabaseDriverSQLite(const QString &connectionName,
                         std::unique_ptr<DatabaseQueryParserStandard> &&queryParser);
    
    virtual bool initializeConnection() override;
    virtual bool executeQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                              std::vector<std::shared_ptr<DatabaseQueryResultBase>> &results) override;
};

#endif // DATABASEDRIVERSQLITE_H
