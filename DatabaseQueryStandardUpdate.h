#ifndef DATABASEQUERYSTANDARDUPDATE_H
#define DATABASEQUERYSTANDARDUPDATE_H

#include "DatabaseQueryStandard.h"

#include "DatabaseQueryUsingCondition.h"
#include "DatabaseQueryUsingValuesList.h"

class DatabaseQueryStandardUpdate
        : public DatabaseQueryStandard,
          public DatabaseQueryUsingCondition,
          public DatabaseQueryUsingValuesList
{
public:
    using ConditionsList = DatabaseQueryUsingCondition::ConditionsList;
    using ValuesList     = DatabaseQueryUsingValuesList::ValuesList;
    
    DatabaseQueryStandardUpdate(const QStringList &tables,
                                const QStringList &attributes,
                                const ValuesList &values,
                                const ConditionsList &conditions = ConditionsList{});

    virtual bool isValid() const override;
};

#endif // DATABASEQUERYSTANDARDUPDATE_H
