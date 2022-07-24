#include "DatabaseEntityProcessorInterface.h"


bool DatabaseEntityProcessorInterface::getEntityByDatabaseQueryResult(const CoreContext::EntityType entityType, 
                                                                      const std::shared_ptr<DatabaseQueryResultBase> &queryResult, 
                                                                      std::vector<std::shared_ptr<EntityBase>> &entities)
{
    switch (entityType) {
    case CoreContext::EntityType::ET_GRADE:   return getEntityGradeByDatabaseQueryResult(queryResult, entities);
    case CoreContext::EntityType::ET_QUOTE:   return getEntityQuoteByDatabaseQueryResult(queryResult, entities);
    case CoreContext::EntityType::ET_SESSION: return getEntitySessionByDatabaseQueryResult(queryResult, entities);
    case CoreContext::EntityType::ET_USER:    return getEntityUserByDatabaseQueryResult(queryResult, entities);
    }
    
    return false;
}
