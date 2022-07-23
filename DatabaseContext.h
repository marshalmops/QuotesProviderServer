#ifndef DATABASECONTEXT_H
#define DATABASECONTEXT_H

#include <stdint.h>

namespace DatabaseContext {

enum DatabaseType : uint8_t {
    DT_INVALID = 0,
    DT_SQLITE,
    DT_MYSQL
};

constexpr static const DatabaseType C_DEFAULT_DATABASE_TYPE = DatabaseType::DT_SQLITE;

using DatabaseQueryTypeType = uint8_t;

enum DatabaseQueryType : DatabaseQueryTypeType {
    DQT_INVALID = 0
};

using DatabaseQueryConditionTypeType = uint8_t;

enum DatabaseQueryConditionType : DatabaseQueryConditionTypeType {
    DQCT_INVALID = 0
};

};

#endif // DATABASECONTEXT_H
