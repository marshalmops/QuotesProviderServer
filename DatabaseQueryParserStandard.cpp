#include "DatabaseQueryParserStandard.h"


bool DatabaseQueryParserStandard::parseQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                                             std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    if (!query->isValid()) return false;
    
    switch (query->getType()) {
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_SELECT: {return parseSelectQuery(dynamic_cast<DatabaseQueryStandardSelect*>(query.get()), result);}
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_INSERT: {return parseInsertQuery(dynamic_cast<DatabaseQueryStandardInsert*>(query.get()), result);}
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_UPDATE: {return parseUpdateQuery(dynamic_cast<DatabaseQueryStandardUpdate*>(query.get()), result);}
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_DELETE: {return parseDeleteQuery(dynamic_cast<DatabaseQueryStandardDelete*>(query.get()), result);}
    }
    
    return false;
}

bool DatabaseQueryParserStandard::parseSelectQuery(const DatabaseQueryStandardSelect * const query,
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    
}

bool DatabaseQueryParserStandard::parseInsertQuery(const DatabaseQueryStandardInsert * const query,
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    
}

bool DatabaseQueryParserStandard::parseUpdateQuery(const DatabaseQueryStandardUpdate * const query,
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    
}

bool DatabaseQueryParserStandard::parseDeleteQuery(const DatabaseQueryStandardDelete * const query, 
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    
}
