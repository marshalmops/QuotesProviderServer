#include "DatabaseQueryUsingCondition.h"

DatabaseQueryUsingCondition::DatabaseQueryUsingCondition(const ConditionsList &conditions)
    : m_conditions{conditions}
{
    
}

DatabaseQueryUsingCondition::DatabaseQueryUsingCondition(const std::initializer_list<std::shared_ptr<DatabaseQueryConditionBase> > &conditions)
    : m_conditions{conditions}
{
    
}

const DatabaseQueryUsingCondition::ConditionsList &DatabaseQueryUsingCondition::getConditions() const
{
    return m_conditions;
}
