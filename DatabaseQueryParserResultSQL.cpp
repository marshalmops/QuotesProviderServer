#include "DatabaseQueryParserResultSQL.h"

const QString &DatabaseQueryParserResultSQL::getSqlString() const
{
    return m_sqlString;
}

bool DatabaseQueryParserResultSQL::isValid() const
{
    return !m_sqlString.isEmpty();
}
