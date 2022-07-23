#include "DatabaseQueryStandardDelete.h"


DatabaseQueryStandardDelete::DatabaseQueryStandardDelete(const QString &table,
                                                         const ConditionsList &conditions)
    : DatabaseQueryStandard{DatabaseQueryContextStandard::DatabaseQueryType::DQT_DELETE, QStringList{table}},
      DatabaseQueryUsingCondition{conditions}
{
    
}
