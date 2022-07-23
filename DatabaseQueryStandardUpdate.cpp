#include "DatabaseQueryStandardUpdate.h"

DatabaseQueryStandardUpdate::DatabaseQueryStandardUpdate(const QStringList &tables,
                                                         const QStringList &attributes,
                                                         const ValuesList &values,
                                                         const ConditionsList &conditions)
    : DatabaseQueryStandard{DatabaseQueryContextStandard::DatabaseQueryType::DQT_UPDATE, tables, attributes},
      DatabaseQueryUsingCondition{conditions},
      DatabaseQueryUsingValuesList{values}
{
    
}
