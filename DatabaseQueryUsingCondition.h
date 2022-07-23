#ifndef DATABASEQUERYUSINGCONDITION_H
#define DATABASEQUERYUSINGCONDITION_H

#include <vector>
#include <memory>

#include "DatabaseQueryConditionBase.h"

class DatabaseQueryUsingCondition
{
public:
    using ConditionsList = std::vector<std::shared_ptr<DatabaseQueryConditionBase>>;
    
    DatabaseQueryUsingCondition(const ConditionsList &conditions);
    DatabaseQueryUsingCondition(const std::initializer_list<std::shared_ptr<DatabaseQueryConditionBase>> &conditions);
    
    const ConditionsList& getConditions() const;
    
protected:
    ConditionsList m_conditions;
};

#endif // DATABASEQUERYUSINGCONDITION_H
