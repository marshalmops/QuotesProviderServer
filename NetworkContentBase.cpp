#include "NetworkContentBase.h"

NetworkContentBase::NetworkContentBase() noexcept
    : m_workerId{0},
      m_socketId{0},
      m_jsonBody{}
{
    
}

NetworkContentBase::NetworkContentBase(const ServerContext::WorkerId workerId,
                                       const ServerContext::SocketId socketId,
                                       const QJsonObject &jsonBody)
    : m_workerId{workerId},
      m_socketId{socketId},
      m_jsonBody{jsonBody}
{
    
}

ServerContext::WorkerId NetworkContentBase::getWorkerId() const
{
    return m_workerId;
}

ServerContext::SocketId NetworkContentBase::getSocketId() const
{
    return m_socketId;
}

const QJsonObject &NetworkContentBase::getJsonBody() const
{
    return m_jsonBody;
}
