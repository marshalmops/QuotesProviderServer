#ifndef DATABASEQUERYRESULTSTANDARD_H
#define DATABASEQUERYRESULTSTANDARD_H

#include <QSqlRecord>

#include "DatabaseQueryResultBase.h"

class DatabaseQueryResultStandard : public DatabaseQueryResultBase
{
public:
    DatabaseQueryResultStandard(const QSqlRecord &sqlResult);
    
    const QSqlRecord& getSqlResult() const;
    
protected:
    QSqlRecord m_sqlResult;
};

#endif // DATABASEQUERYRESULTSTANDARD_H
