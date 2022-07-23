#ifndef DATABASEQUERYSTANDARDINSERT_H
#define DATABASEQUERYSTANDARDINSERT_H

#include "DatabaseQueryStandard.h"

#include "DatabaseQueryUsingValuesList.h"

class DatabaseQueryStandardInsert
        : public DatabaseQueryStandard,
          public DatabaseQueryUsingValuesList
{
public:
    using ValuesList = DatabaseQueryUsingValuesList::ValuesList;
    
    DatabaseQueryStandardInsert(const QString &table,
                                const ValuesList &values,
                                const QStringList &attributes = QStringList{});
};

#endif // DATABASEQUERYSTANDARDINSERT_H
