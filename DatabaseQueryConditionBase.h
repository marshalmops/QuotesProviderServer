#ifndef DATABASEQUERYCONDITIONBASE_H
#define DATABASEQUERYCONDITIONBASE_H

#include "DatabaseContext.h"

class DatabaseQueryConditionBase
{
public:
    DatabaseQueryConditionBase(const DatabaseContext::DatabaseQueryConditionTypeType type = DatabaseContext::DatabaseQueryConditionType::DQCT_INVALID);
    virtual ~DatabaseQueryConditionBase() = default;
    
    DatabaseContext::DatabaseQueryConditionTypeType getType() const;
    
    virtual bool isValid() const = 0;
    
protected:
    DatabaseContext::DatabaseQueryConditionTypeType m_type;
};

#endif // DATABASEQUERYCONDITIONBASE_H
