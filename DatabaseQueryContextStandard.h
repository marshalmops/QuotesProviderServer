#ifndef DATABASEQUERYCONTEXTSTANDARD_H
#define DATABASEQUERYCONTEXTSTANDARD_H

#include <stdint.h>

#include "DatabaseContext.h"

namespace DatabaseQueryContextStandard
{

enum DatabaseQueryType : DatabaseContext::DatabaseQueryTypeType {
    DQT_SELECT = DatabaseContext::DatabaseType::DT_INVALID + 1,
    DQT_INSERT,
    DQT_UPDATE,
    DQT_DELETE
};

enum DatabaseQueryConditionType : DatabaseContext::DatabaseQueryConditionTypeType {
    DQCT_GREATER_THEN = DatabaseContext::DatabaseQueryConditionType::DQCT_INVALID + 1,
    DQCT_LESS_THEN,
    DQCT_EQUAL_TO,
    DQCT_LIKE
};

enum OrderFlag : uint8_t {
    OF_NO_ORDER = 0,
    OF_ASC,
    OF_DESC
};

};

#endif // DATABASEQUERYCONTEXTSTANDARD_H
