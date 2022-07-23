#ifndef DATABASEQUERYSTANDARDSELECT_H
#define DATABASEQUERYSTANDARDSELECT_H

#include "DatabaseQueryStandard.h"

#include "DatabaseQueryUsingCondition.h"

class DatabaseQueryStandardSelect
        : public DatabaseQueryStandard,
          public DatabaseQueryUsingCondition
{
public:
    using ConditionsList = DatabaseQueryUsingCondition::ConditionsList;
    
    DatabaseQueryStandardSelect(const QStringList &tables,
                                const QStringList &attributes = QStringList{},
                                const ConditionsList &conditions = ConditionsList{},
                                const uint32_t limit = 0,
                                const DatabaseQueryContextStandard::OrderFlag orderFlag = DatabaseQueryContextStandard::OrderFlag::OF_NO_ORDER,
                                const QString &orderAttribute = QString{});
    
    uint32_t getLimit() const;
    DatabaseQueryContextStandard::OrderFlag getOrder() const;
    const QString& getOrderAttribute() const;
    
protected:
    uint32_t m_limit;
    DatabaseQueryContextStandard::OrderFlag m_orderFlag;
    QString m_orderAttribute;
};

#endif // DATABASEQUERYSTANDARDSELECT_H
