#ifndef DATABASEDRIVERSTANDARD_H
#define DATABASEDRIVERSTANDARD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "DatabaseDriverBase.h"

#include "DatabaseQueryResultStandard.h"

#include "DatabaseQueryParserStandard.h"

class DatabaseDriverStandard : public DatabaseDriverBase
{
public:
    DatabaseDriverStandard(const QString &connectionName,
                           std::unique_ptr<DatabaseQueryParserStandard> &&queryParser);

protected:
    QString m_connectionName;
};

#endif // DATABASEDRIVERSTANDARD_H
