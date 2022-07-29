#include "DatabaseQueryParserResultSQL.h"

DatabaseQueryParserResultSQL::DatabaseQueryParserResultSQL(const QString &sqlString)
    : m_sqlString{sqlString}
{
    
}

const QString &DatabaseQueryParserResultSQL::getSqlString() const
{
    return m_sqlString;
}

bool DatabaseQueryParserResultSQL::isValid() const
{
    return !m_sqlString.isEmpty();
}
