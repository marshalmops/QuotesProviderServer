#ifndef NETWORKCONTENTBASE_H
#define NETWORKCONTENTBASE_H

#include <QJsonObject>
#include <QJsonDocument>

#include "ServerContext.h"

class NetworkContentBase
{
public:
    NetworkContentBase() noexcept;
    NetworkContentBase(const ServerContext::WorkerId workerId,
                       const ServerContext::SocketId socketId,
                       const QJsonObject &jsonBody);
    virtual ~NetworkContentBase() = default;
    
    ServerContext::WorkerId getWorkerId() const;
    ServerContext::SocketId getSocketId() const;
    const QJsonObject&      getJsonBody() const;
    
    virtual bool fromRawData(const ServerContext::RawData &rawData) = 0;
    virtual bool isValid    ()                                const = 0;
    
protected:
    ServerContext::WorkerId m_workerId;
    ServerContext::SocketId m_socketId;
    QJsonObject m_jsonBody;
};

#endif // NETWORKCONTENTBASE_H
