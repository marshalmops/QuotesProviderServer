#include "DatabaseQueryStandardSelect.h"

DatabaseQueryStandardSelect::DatabaseQueryStandardSelect(const QStringList &tables,
                                                         const QStringList &attributes, 
                                                         const ConditionsList &conditions,
                                                         const uint32_t limit,
                                                         const OrderingPairsList &orderingPairs)
    : DatabaseQueryStandard{DatabaseQueryContextStandard::DatabaseQueryType::DQT_SELECT, tables, attributes},
      DatabaseQueryUsingCondition{conditions},
      m_limit{limit},
      m_orderingPairs{orderingPairs}
{
    
}

uint32_t DatabaseQueryStandardSelect::getLimit() const
{
    return m_limit;
}

const DatabaseQueryStandardSelect::OrderingPairsList &DatabaseQueryStandardSelect::getOrderingPairs() const
{
    return m_orderingPairs;
}

bool DatabaseQueryStandardSelect::isValid() const
{
    if (!m_orderingPairs.empty()) {
        for (auto i = m_orderingPairs.begin(); i != m_orderingPairs.end(); ++i) {
            if (i->first == DatabaseQueryContextStandard::OrderFlag::OF_NO_ORDER
             || i->second.isEmpty())
            {
                return false;
            }
        }
    }
    
    return DatabaseQueryStandard::isValid();
}
