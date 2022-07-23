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

    virtual bool isValid() const override;
};

#endif // DATABASEQUERYSTANDARDINSERT_H
