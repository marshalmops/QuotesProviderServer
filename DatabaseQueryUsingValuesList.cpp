#include "DatabaseQueryUsingValuesList.h"

DatabaseQueryUsingValuesList::DatabaseQueryUsingValuesList(const ValuesList &values)
    : m_values{values}
{
    
}

DatabaseQueryUsingValuesList::DatabaseQueryUsingValuesList(const std::initializer_list<QVariant> &values)
    : m_values{values}
{
    
}

const DatabaseQueryUsingValuesList::ValuesList &DatabaseQueryUsingValuesList::getValues() const
{
    return m_values;
}
