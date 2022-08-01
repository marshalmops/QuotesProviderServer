#include "DatabaseQueryResultStandard.h"

DatabaseQueryResultStandard::DatabaseQueryResultStandard(const QSqlRecord &sqlResult)
    : m_sqlResult{sqlResult}
{
    
}

const QSqlRecord &DatabaseQueryResultStandard::getSqlResult() const
{
    return m_sqlResult;
}
