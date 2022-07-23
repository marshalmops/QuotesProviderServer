#ifndef DATABASEQUERYRESULTSTANDARD_H
#define DATABASEQUERYRESULTSTANDARD_H

#include <QSqlQuery>

#include "DatabaseQueryResultBase.h"

class DatabaseQueryResultStandard : public DatabaseQueryResultBase
{
public:
    DatabaseQueryResultStandard(const QSqlQuery &sqlResult);
    
    const QSqlQuery& getSqlResult() const;
    
protected:
    QSqlQuery m_sqlResult;
};

#endif // DATABASEQUERYRESULTSTANDARD_H
