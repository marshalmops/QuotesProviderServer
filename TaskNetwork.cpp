#include "TaskNetwork.h"

TaskNetwork::TaskNetwork(const std::shared_ptr<NetworkContentRequest> &request)
    : TaskBase{CoreContext::TaskType::TT_NETWORK_TASK},
      m_request{request}
{
    
}

const std::shared_ptr<NetworkContentRequest> &TaskNetwork::getRequest() const
{
    return m_request;
}
