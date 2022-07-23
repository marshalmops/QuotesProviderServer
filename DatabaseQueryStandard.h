#ifndef DATABASEQUERYSTANDARD_H
#define DATABASEQUERYSTANDARD_H

#include "DatabaseQueryBase.h"

#include "DatabaseQueryContextStandard.h"

class DatabaseQueryStandard : public DatabaseQueryBase
{
public:
    DatabaseQueryStandard(const DatabaseContext::DatabaseQueryTypeType type,
                          const QStringList &tables,
                          const QStringList &attributes = QStringList{});
    
    const QStringList& getAttributes() const;
    const QStringList& getTables    () const;
    
    virtual bool isValid() const override;
    
protected:
    QStringList m_attributes;
    QStringList m_tables;
};

#endif // DATABASEQUERYSTANDARD_H
