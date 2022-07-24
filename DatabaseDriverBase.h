#ifndef DATABASEDRIVERBASE_H
#define DATABASEDRIVERBASE_H

#include "DatabaseQueryParserInterface.h"

#include "DatabaseSettingsContainerBase.h"

#include "DatabaseQueryBase.h"
#include "DatabaseQueryResultBase.h"

class DatabaseDriverBase
{
public:
    DatabaseDriverBase(std::unique_ptr<DatabaseQueryParserInterface> &&queryParser);
    virtual ~DatabaseDriverBase() = default;
    
    virtual bool initializeConnection() = 0;
    virtual bool executeQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                              std::vector<std::shared_ptr<DatabaseQueryResultBase>> &results) = 0;
    
protected:
    std::unique_ptr<DatabaseQueryParserInterface> m_queryParser;
};

#endif // DATABASEDRIVERBASE_H
