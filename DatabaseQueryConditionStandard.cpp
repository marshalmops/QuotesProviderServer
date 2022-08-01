#include "DatabaseQueryConditionStandard.h"

namespace {

QString variantToDatabaseString(const QVariant &variant) {
    QString result{};
    
    switch (variant.type()) {
    case QVariant::Type::Bool: 
    case QVariant::Type::UInt:
    case QVariant::Type::Int: 
    case QVariant::Type::ULongLong: 
    case QVariant::Type::LongLong:
    case QVariant::Type::Double: result = variant.toString();
    case QVariant::Type::String: result = ('\'' + variant.toString() + '\'');
    }
    
    return result;
}

}

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

QString DatabaseQueryConditionStandard::toString() const
{
    QString conditionString{};
    
    conditionString += (m_attributeName + ' ');
    
    switch (static_cast<DatabaseQueryContextStandard::DatabaseQueryConditionType>(m_type)) {
    case DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO:     {conditionString += '='; break;}
    case DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_GREATER_THEN: {conditionString += '>'; break;}
    case DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_LESS_THEN:    {conditionString += '<'; break;}
    case DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_LIKE:         {conditionString += "LIKE"; break;}
    default: return QString{};
    }
    
    conditionString += (' ' + variantToDatabaseString(m_value));
    
    return conditionString;
}

bool DatabaseQueryConditionStandard::isValid() const
{
    return (m_type != DatabaseContext::DatabaseQueryType::DQT_INVALID
        && !m_attributeName.isEmpty());
}
