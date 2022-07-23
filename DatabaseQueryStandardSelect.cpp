#include "DatabaseQueryStandardSelect.h"

DatabaseQueryStandardSelect::DatabaseQueryStandardSelect(const QStringList &tables,
                                                         const QStringList &attributes, 
                                                         const ConditionsList &conditions,
                                                         const uint32_t limit,
                                                         const DatabaseQueryContextStandard::OrderFlag orderFlag,
                                                         const QString &orderAttribute)
    : DatabaseQueryStandard{DatabaseQueryContextStandard::DatabaseQueryType::DQT_SELECT, tables, attributes},
      DatabaseQueryUsingCondition{conditions},
      m_limit{limit},
      m_orderFlag{orderFlag},
      m_orderAttribute{orderAttribute}
{
    
}

uint32_t DatabaseQueryStandardSelect::getLimit() const
{
    return m_limit;
}

DatabaseQueryContextStandard::OrderFlag DatabaseQueryStandardSelect::getOrder() const
{
    return m_orderFlag;
}

const QString &DatabaseQueryStandardSelect::getOrderAttribute() const
{
    return m_orderAttribute;
}
