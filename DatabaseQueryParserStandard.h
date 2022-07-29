#ifndef DATABASEQUERYPARSERSTANDARD_H
#define DATABASEQUERYPARSERSTANDARD_H

#include "DatabaseQueryParserInterface.h"

#include "DatabaseQueryStandardSelect.h"
#include "DatabaseQueryStandardInsert.h"
#include "DatabaseQueryStandardUpdate.h"
#include "DatabaseQueryStandardDelete.h"

#include "DatabaseQueryConditionStandard.h"

#include "DatabaseQueryParserResultSQL.h"

class DatabaseQueryParserStandard : public DatabaseQueryParserInterface
{
public:
    DatabaseQueryParserStandard() = default;
    
    virtual bool parseQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                            std::unique_ptr<DatabaseQueryParserResultInterface> &result) override;

protected:
    virtual bool parseSelectQuery(const DatabaseQueryStandardSelect *const query,
                                  std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    virtual bool parseInsertQuery(const DatabaseQueryStandardInsert *const query,
                                  std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    virtual bool parseUpdateQuery(const DatabaseQueryStandardUpdate *const query,
                                  std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    virtual bool parseDeleteQuery(const DatabaseQueryStandardDelete *const query,
                                  std::unique_ptr<DatabaseQueryParserResultInterface> &result);
    
    QString orderFlagToString     (const DatabaseQueryContextStandard::OrderFlag orderFlag) const;
    QString variantValueToString  (const QVariant &value) const;
    QString conditionsListToString(const DatabaseQueryUsingCondition::ConditionsList &conditions) const;
};

#endif // DATABASEQUERYPARSERSTANDARD_H
