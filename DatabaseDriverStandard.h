#ifndef DATABASEDRIVERSTANDARD_H
#define DATABASEDRIVERSTANDARD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "DatabaseDriverBase.h"

#include "DatabaseQueryResultStandard.h"

#include "DatabaseQueryParserStandard.h"

class DatabaseDriverStandard : public DatabaseDriverBase
{
public:
    DatabaseDriverStandard(const QString &connectionName,
                           std::unique_ptr<DatabaseQueryParserStandard> &&queryParser);
    virtual ~DatabaseDriverStandard() override;
    
    virtual bool executeRawQuery(const QString &rawQuery,
                                 std::vector<std::shared_ptr<DatabaseQueryResultBase>> &results) override;

    bool checkTablesOnExisting(const QStringList &tablesToCheck);
    
protected:
    QString m_connectionName;
};

#endif // DATABASEDRIVERSTANDARD_H
