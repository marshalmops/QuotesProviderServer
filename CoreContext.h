#ifndef CORECONTEXT_H
#define CORECONTEXT_H

#include <stdint.h>


namespace CoreContext
{

enum TaskType : uint8_t {
    TT_INVALID = 0,
    TT_CORE_TASK,
    TT_NETWORK_TASK
};

enum CoreTaskType : uint8_t {
    CTT_INVALID = 0,
    CTT_GET_RANDOM_QUOTE
};

enum EntityType : uint8_t {
    ET_INVALID = 0,
    ET_GRADE,
    ET_QUOTE,
    ET_USER,
    ET_SESSION,
    ET_ENTITY_RIGHTS_GROUP
};

};

#endif // CORECONTEXT_H
