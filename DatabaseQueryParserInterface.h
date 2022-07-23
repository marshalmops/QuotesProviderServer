#ifndef DATABASEQUERYPARSERINTERFACE_H
#define DATABASEQUERYPARSERINTERFACE_H

#include <memory>

#include "DatabaseQueryParserResultInterface.h"
#include "DatabaseQueryBase.h"

class DatabaseQueryParserInterface
{
public:
    DatabaseQueryParserInterface() = default;
    virtual ~DatabaseQueryParserInterface() = default;
    
    virtual bool parseQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                            std::unique_ptr<DatabaseQueryParserResultInterface> &result) = 0;
};

#endif // DATABASEQUERYPARSERINTERFACE_H
