#ifndef NETWORKCONTENTRESPONSE
#define NETWORKCONTENTRESPONSE

#include "NetworkContentBase.h"

class NetworkContentResponse : public NetworkContentBase
{
public:
    enum ResponseProcessingCode : uint8_t {
        RPC_INVALID = 0,
        RPC_NOT_FOUND,
        RPC_ALREADY_EXISTS,
        RPC_OK
    };
    
    NetworkContentResponse() = delete;
    NetworkContentResponse(const ServerContext::WorkerId workerId,
                           const ServerContext::SocketId socketId,
                           const ResponseProcessingCode code = RPC_INVALID,
                           const QJsonObject &jsonBody = QJsonObject());
    
    //virtual bool fromRawData(const ServerContext::RawData &rawData) override;
    bool toRawData(ServerContext::RawData &rawData);
    virtual bool isValid() const override;
    
    ResponseProcessingCode getResponseProcessingCode() const;
    
protected:
    ResponseProcessingCode m_code;
};

Q_DECLARE_METATYPE(std::shared_ptr<NetworkContentResponse>)

#endif // NETWORKCONTENTRESPONSE
