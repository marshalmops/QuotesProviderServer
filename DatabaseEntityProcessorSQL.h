#ifndef DATABASEENTITYPROCESSORSQL_H
#define DATABASEENTITYPROCESSORSQL_H

#include <QVariant>

#include "DatabaseEntityProcessorInterface.h"

#include "DatabaseQueryResultStandard.h"

class DatabaseEntityProcessorSQL : public DatabaseEntityProcessorInterface
{
public:
    DatabaseEntityProcessorSQL() = default;
    
protected:
    virtual bool getEntityGradeByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                     std::vector<std::shared_ptr<EntityBase>> &entities) override;
    virtual bool getEntityUserByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                    std::vector<std::shared_ptr<EntityBase>> &entities) override;
    virtual bool getEntitySessionByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                       std::vector<std::shared_ptr<EntityBase>> &entities) override;
    virtual bool getEntityQuoteByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                     std::vector<std::shared_ptr<EntityBase>> &entities) override;
};

#endif // DATABASEENTITYPROCESSORSQL_H
