#ifndef TASKBASE_H
#define TASKBASE_H

#include "CoreContext.h"

class TaskBase
{
public:
    TaskBase         (const CoreContext::TaskType taskType = CoreContext::TaskType::TT_INVALID);
    virtual ~TaskBase() = default;
    
    CoreContext::TaskType getTaskType() const;
    
protected:
    CoreContext::TaskType m_taskType;
};

#endif // TASKBASE_H
