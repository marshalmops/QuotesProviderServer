#include "DatabaseQueryResultStandard.h"

DatabaseQueryResultStandard::DatabaseQueryResultStandard(const QSqlQuery &sqlResult)
    : m_sqlResult{sqlResult}
{
    
}

const QSqlQuery &DatabaseQueryResultStandard::getSqlResult() const
{
    return m_sqlResult;
}
