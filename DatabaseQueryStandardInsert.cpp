#include "DatabaseQueryStandardInsert.h"

DatabaseQueryStandardInsert::DatabaseQueryStandardInsert(const QString &table,
                                                         const ValuesList &values,
                                                         const QStringList &attributes)
    : DatabaseQueryStandard{DatabaseQueryContextStandard::DatabaseQueryType::DQT_INSERT, QStringList{table}, attributes},
      DatabaseQueryUsingValuesList{values}
{
    
}
