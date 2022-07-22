#include "NetworkContentResponse.h"

NetworkContentResponse::NetworkContentResponse(const ServerContext::WorkerId workerId,
                                               const ServerContext::SocketId socketId,
                                               const ResponseProcessingCode code,
                                               const QJsonObject &jsonBody)
    : NetworkContentBase(workerId, socketId, jsonBody),
      m_code{code}
{
    
}

bool NetworkContentResponse::fromRawData(const ServerContext::RawData &rawData)
{
    size_t curIndex = 0;
    
    auto rawJsonBody = rawData.substr(curIndex);
    auto jsonBody    = QJsonDocument::fromJson(QByteArray{rawJsonBody.data()}).object();
    
    m_jsonBody = jsonBody;
    
    return true;
}

bool NetworkContentResponse::toRawData(ServerContext::RawData &rawData)
{
    QJsonDocument          jsonBodyDoc  {m_jsonBody};
    ServerContext::RawData rawDataBuffer{jsonBodyDoc.toJson().data()};
    
    if (rawDataBuffer.empty()) return false;
    
    rawData = std::move(rawDataBuffer);
    
    return true;
}

bool NetworkContentResponse::isValid() const
{
    return (m_code != ResponseProcessingCode::RPC_INVALID);
}

NetworkContentResponse::ResponseProcessingCode NetworkContentResponse::getResponseProcessingCode() const
{
    return m_code;
}
