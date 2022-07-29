#include "TaskBase.h"

TaskBase::TaskBase(const CoreContext::TaskType taskType)
    : m_taskType{taskType}
{
    
}

CoreContext::TaskType TaskBase::getTaskType() const
{
    return m_taskType;
}

bool TaskBase::isValid()
{
    return (m_taskType != CoreContext::TaskType::TT_INVALID);
}
