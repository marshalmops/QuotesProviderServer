#include "DatabaseQueryBase.h"

DatabaseQueryBase::DatabaseQueryBase(const DatabaseContext::DatabaseQueryTypeType type)
    : m_type{type}
{
    
}

DatabaseContext::DatabaseQueryTypeType DatabaseQueryBase::getType() const
{
    return m_type;
}
