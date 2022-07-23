#ifndef DATABASEQUERYSTANDARDSELECT_H
#define DATABASEQUERYSTANDARDSELECT_H

#include "DatabaseQueryStandard.h"

#include "DatabaseQueryUsingCondition.h"

class DatabaseQueryStandardSelect
        : public DatabaseQueryStandard,
          public DatabaseQueryUsingCondition
{
public:
    using OrderingPairsList = std::vector<std::pair<DatabaseQueryContextStandard::OrderFlag, QString>>;
    using ConditionsList    = DatabaseQueryUsingCondition::ConditionsList;
    
    DatabaseQueryStandardSelect(const QStringList &tables,
                                const QStringList &attributes = QStringList{},
                                const ConditionsList &conditions = ConditionsList{},
                                const uint32_t limit = 0,
                                const OrderingPairsList &orderingPairs = OrderingPairsList{});
    
    uint32_t getLimit() const;
    const OrderingPairsList& getOrderingPairs() const;
    
    virtual bool isValid() const override;
    
protected:
    uint32_t m_limit;
    OrderingPairsList m_orderingPairs;
};

#endif // DATABASEQUERYSTANDARDSELECT_H
