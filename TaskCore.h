#ifndef TASKCORE_H
#define TASKCORE_H

#include "TaskBase.h"

class TaskCore : public TaskBase
{
public:
    TaskCore(const CoreContext::CoreTaskType coreTaskType = CoreContext::CoreTaskType::CTT_INVALID);
    
    CoreContext::CoreTaskType getCoreTaskType() const;
    
    virtual bool isValid() override;
    
protected:
    CoreContext::CoreTaskType m_coreTaskType;
};

#endif // TASKCORE_H
