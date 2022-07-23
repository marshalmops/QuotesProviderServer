#include "DatabaseQueryStandard.h"


DatabaseQueryStandard::DatabaseQueryStandard(const DatabaseContext::DatabaseQueryTypeType type,
                                             const QStringList &tables,
                                             const QStringList &attributes)
    : DatabaseQueryBase{type},
      m_attributes{attributes},
      m_tables{tables}
{
    
}

const QStringList &DatabaseQueryStandard::getAttributes() const
{
    return m_attributes;
}

const QStringList &DatabaseQueryStandard::getTables() const
{
    return m_tables;
}

bool DatabaseQueryStandard::isValid() const
{
    return (!m_tables.isEmpty() && DatabaseQueryBase::isValid());
}
