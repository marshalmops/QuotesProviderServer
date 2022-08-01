#ifndef NETWORKCONTENTREQUEST_H
#define NETWORKCONTENTREQUEST_H

#include "NetworkContentBase.h"

class NetworkContentRequest : public NetworkContentBase
{
public:
    NetworkContentRequest() = delete;
    NetworkContentRequest(const ServerContext::WorkerId workerId,
                          const ServerContext::SocketId socketId,
                          const ServerContext::EndpointId endpointId = ServerContext::Endpoints::E_INVALID,
                          const QJsonObject &jsonBody = QJsonObject());
    
    ServerContext::EndpointId getEndpointId() const;
    
    //virtual bool fromRawData(const ServerContext::RawData &rawData) override;
    virtual bool isValid() const override;
    
    bool fromRequestBase(const ServerContext::EndpointId endpoint,
                         const ServerContext::RawData &rawJson);
    
private:
    ServerContext::EndpointId m_endpointId;
};

Q_DECLARE_METATYPE(std::shared_ptr<NetworkContentRequest>)

#endif // NETWORKCONTENTREQUEST_H
