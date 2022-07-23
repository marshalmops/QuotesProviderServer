#include "DatabaseQueryConditionStandard.h"

DatabaseQueryConditionStandard::DatabaseQueryConditionStandard(const DatabaseContext::DatabaseQueryConditionTypeType type,
                                                               const QString &attributeName,
                                                               const QVariant &value)
    : DatabaseQueryConditionBase{type},
      m_attributeName{attributeName},
      m_value{value}
{
    
}

const QString &DatabaseQueryConditionStandard::getAttributeName() const
{
    return m_attributeName;
}

const QVariant &DatabaseQueryConditionStandard::getValue() const
{
    return m_value;
}

bool DatabaseQueryConditionStandard::isValid() const
{
    return (m_type != DatabaseContext::DatabaseQueryType::DQT_INVALID
        && !m_attributeName.isEmpty());
}
