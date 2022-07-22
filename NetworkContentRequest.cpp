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

bool NetworkContentRequest::fromRawData(const ServerContext::RawData &rawData)
{
    if (rawData.length() < sizeof(ServerContext::EndpointId)) return false;
    
    size_t curIndex = 0;
    
    auto rawEndpointId = rawData.substr(curIndex, sizeof(ServerContext::EndpointId));
    
    if (rawEndpointId.empty()) return false;
    
    curIndex += sizeof(ServerContext::EndpointId);
    
    auto rawJsonBody = rawData.substr(curIndex);
    
    auto endpointId = std::stoi(rawEndpointId);
    auto jsonBody   = QJsonDocument::fromJson(QByteArray{rawJsonBody.data()}).object();
    
    if (endpointId == ServerContext::Endpoints::E_INVALID)
        return false;
    
    m_endpointId = endpointId;
    m_jsonBody   = jsonBody;
    
    return true;
}

bool NetworkContentRequest::isValid() const
{
    return (m_endpointId != ServerContext::Endpoints::E_INVALID);
}
