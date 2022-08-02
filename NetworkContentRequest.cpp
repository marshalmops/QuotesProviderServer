#include "NetworkContentRequest.h"


NetworkContentRequest::NetworkContentRequest(const ServerContext::WorkerId workerId,
                                             const ServerContext::SocketId socketId,
                                             const ServerContext::EndpointId endpointId,
                                             const QJsonObject &jsonBody)
    : NetworkContentBase(workerId, socketId, jsonBody),
      m_endpointId{endpointId}
{
    
}

ServerContext::EndpointId NetworkContentRequest::getEndpointId() const
{
    return m_endpointId;
}

bool NetworkContentRequest::isValid() const
{
    return (m_endpointId != ServerContext::Endpoints::E_INVALID);
}

bool NetworkContentRequest::fromRequestBase(const ServerContext::EndpointId endpoint,
                                            const ServerContext::RawData &rawJson)
{
    if (endpoint == ServerContext::Endpoints::E_INVALID)
        return false;
    
    if (!rawJson.empty()) {
        auto jsonBody = QJsonDocument::fromJson(QByteArray{rawJson.data()}).object();
        
        if (jsonBody.isEmpty())
            return false;
        
        m_jsonBody = std::move(jsonBody);
    }
    
    m_endpointId = endpoint;
    
    return true;
}
