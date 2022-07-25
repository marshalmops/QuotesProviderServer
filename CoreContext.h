#ifndef CORECONTEXT_H
#define CORECONTEXT_H

#include <stdint.h>
#include <QString>

namespace CoreContext
{

using Id   = uint64_t;
using Hash = QString;

enum TaskType : uint8_t {
    TT_INVALID = 0,
    TT_CORE_TASK,
    TT_NETWORK_TASK
};

enum CoreTaskType : uint8_t {
    CTT_INVALID = 0,
    CTT_GET_DAILY_QUOTE,
    CTT_GET_HOURLY_QUOTE
};

enum EntityType : uint8_t {
    ET_INVALID = 0,
    ET_GRADE,
    ET_QUOTE,
    ET_USER,
    ET_SESSION,
    ET_ENTITY_RIGHTS_GROUP
};

enum QuoteGrade : uint8_t {
    QG_INVALID = 0,
    QG_LIKE,
    QG_DISLIKE
};

};

#endif // CORECONTEXT_H
