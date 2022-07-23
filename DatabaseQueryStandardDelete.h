#ifndef DATABASEQUERYSTANDARDDELETE_H
#define DATABASEQUERYSTANDARDDELETE_H

#include "DatabaseQueryStandard.h"

#include "DatabaseQueryUsingCondition.h"

class DatabaseQueryStandardDelete
        : public DatabaseQueryStandard,
          public DatabaseQueryUsingCondition
{
public:
    using ConditionsList = DatabaseQueryUsingCondition::ConditionsList;
    
    DatabaseQueryStandardDelete(const QString &table,
                                const ConditionsList &conditions = ConditionsList{});

    virtual bool isValid() const override;
};

#endif // DATABASEQUERYSTANDARDDELETE_H
