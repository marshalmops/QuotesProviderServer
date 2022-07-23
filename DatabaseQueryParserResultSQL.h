#ifndef DATABASEQUERYPARSERRESULTSQL_H
#define DATABASEQUERYPARSERRESULTSQL_H

#include <QString>

#include "DatabaseQueryParserResultInterface.h"

class DatabaseQueryParserResultSQL : public DatabaseQueryParserResultInterface
{
public:
    DatabaseQueryParserResultSQL(const QString &sqlString);
    
    const QString& getSqlString() const;
    
    virtual bool isValid() const override;
    
protected:
    QString m_sqlString;
};

#endif // DATABASEQUERYPARSERRESULTSQL_H
