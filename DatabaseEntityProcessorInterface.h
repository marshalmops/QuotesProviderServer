#ifndef DATABASEENTITYPROCESSORINTERFACE_H
#define DATABASEENTITYPROCESSORINTERFACE_H

#include <memory>
#include <vector>

#include "DatabaseQueryResultBase.h"

#include "EntityBase.h"

#include "EntityGrade.h"
#include "EntityQuote.h"
#include "EntitySession.h"
#include "EntityUser.h"

class DatabaseEntityProcessorInterface
{
public:
    DatabaseEntityProcessorInterface() = default;
    virtual ~DatabaseEntityProcessorInterface() = default;
    
    bool getEntityByDatabaseQueryResult(const CoreContext::EntityType entityType,
                                        const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                        std::vector<std::shared_ptr<EntityBase>> &entities);
    
protected:
    virtual bool getEntityGradeByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                     std::vector<std::shared_ptr<EntityBase>> &entities) = 0;
    virtual bool getEntityUserByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                    std::vector<std::shared_ptr<EntityBase>> &entities) = 0;
    virtual bool getEntitySessionByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                       std::vector<std::shared_ptr<EntityBase>> &entities) = 0;
    virtual bool getEntityQuoteByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                     std::vector<std::shared_ptr<EntityBase>> &entities) = 0;
};

#endif // DATABASEENTITYPROCESSORINTERFACE_H
