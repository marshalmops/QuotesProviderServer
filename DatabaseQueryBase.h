#ifndef DATABASEQUERYBASE_H
#define DATABASEQUERYBASE_H

#include <QStringList>

#include "DatabaseContext.h"

class DatabaseQueryBase
{
public:
    DatabaseQueryBase(const DatabaseContext::DatabaseQueryTypeType type = DatabaseContext::DatabaseQueryType::DQT_INVALID);
    
    DatabaseContext::DatabaseQueryTypeType getType() const;
    
    virtual bool isValid() const;
    
protected:
    DatabaseContext::DatabaseQueryTypeType m_type;
};

#endif // DATABASEQUERYBASE_H
