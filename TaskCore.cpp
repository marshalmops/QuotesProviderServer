#include "TaskCore.h"

TaskCore::TaskCore(const CoreContext::CoreTaskType coreTaskType)
    : TaskBase{CoreContext::TaskType::TT_CORE_TASK},
      m_coreTaskType{coreTaskType}
{
    
}

CoreContext::CoreTaskType TaskCore::getCoreTaskType() const
{
    return m_coreTaskType;
}
