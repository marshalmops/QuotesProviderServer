#ifndef DATABASEQUERYPARSERSTANDARD_H
#define DATABASEQUERYPARSERSTANDARD_H

#include "DatabaseQueryParserInterface.h"

#include "DatabaseQueryStandardSelect.h"
#include "DatabaseQueryStandardInsert.h"
#include "DatabaseQueryStandardUpdate.h"
#include "DatabaseQueryStandardDelete.h"

class DatabaseQueryParserStandard : public DatabaseQueryParserInterface
{
public:
    DatabaseQueryParserStandard();
    
    virtual bool parseQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                            std::unique_ptr<DatabaseQueryParserResultInterface> &result) override;

protected:
    bool parseSelectQuery(const DatabaseQueryStandardSelect *const query,
                          std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    bool parseInsertQuery(const DatabaseQueryStandardInsert *const query,
                          std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    bool parseUpdateQuery(const DatabaseQueryStandardUpdate *const query,
                          std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    bool parseDeleteQuery(const DatabaseQueryStandardDelete *const query,
                          std::unique_ptr<DatabaseQueryParserResultInterface> &result);
};

#endif // DATABASEQUERYPARSERSTANDARD_H
