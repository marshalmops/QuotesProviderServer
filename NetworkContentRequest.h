#ifndef NETWORKCONTENTREQUEST_H
#define NETWORKCONTENTREQUEST_H

#include "NetworkContentBase.h"

class NetworkContentRequest : public NetworkContentBase
{
public:
    NetworkContentRequest() = delete;
    NetworkContentRequest(const ServerContext::WorkerId workerId,
                          const ServerContext::SocketId socketId,
                          const ServerContext::EndpointId endpointId,
                          const QJsonObject &jsonBody = QJsonObject());
    
    ServerContext::EndpointId getEndpointId() const;
    
    virtual bool fromRawData(const ServerContext::RawData &rawData) override;
    virtual bool isValid() const override;
    
private:
    ServerContext::EndpointId m_endpointId;
};

#endif // NETWORKCONTENTREQUEST_H
