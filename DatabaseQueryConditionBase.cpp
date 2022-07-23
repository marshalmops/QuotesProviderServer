#include "DatabaseQueryConditionBase.h"

DatabaseQueryConditionBase::DatabaseQueryConditionBase(const DatabaseContext::DatabaseQueryConditionTypeType type)
    : m_type{type}
{
    
}

DatabaseContext::DatabaseQueryConditionTypeType DatabaseQueryConditionBase::getType() const
{
    return m_type;
}
