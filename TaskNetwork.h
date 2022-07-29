#ifndef TASKNETWORK_H
#define TASKNETWORK_H

#include "TaskBase.h"

#include "NetworkContentRequest.h"

class TaskNetwork : public TaskBase
{
public:
    TaskNetwork(const std::shared_ptr<NetworkContentRequest>& request);
    
    const std::shared_ptr<NetworkContentRequest>& getRequest() const;
    
    virtual bool isValid() override;
    
protected:
    std::shared_ptr<NetworkContentRequest> m_request;
};

#endif // TASKNETWORK_H
