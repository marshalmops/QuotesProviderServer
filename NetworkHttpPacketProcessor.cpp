#include "NetworkHttpPacketProcessor.h"

NetworkHttpPacketProcessor::PacketProcessingResult NetworkHttpPacketProcessor::createRequestByHttpData(const ServerContext::HttpRequest * const httpRequest,
                                                                                                       NetworkContentRequest * const request)
{
    if (!httpRequest) return PacketProcessingResult::PPR_FAIL;
    
    if (httpRequest->method() != boost::beast::http::verb::post)
        return PacketProcessingResult::PPR_INCORRECT_DATA;
    
    auto endpointPath = httpRequest->base().target();

    if (endpointPath.empty())
        return PacketProcessingResult::PPR_INCORRECT_DATA;
    
    QString                  endpointString{QString{endpointPath.to_string().c_str()}.mid(1)};
    ServerContext::Endpoints endpointId    {ServerContext::getEndpointIdByStringHash(endpointString)};
    
    if (endpointId == ServerContext::Endpoints::E_INVALID)
        return PacketProcessingResult::PPR_INCORRECT_DATA;
    
    auto rawJsonBody = httpRequest->body().data();
   
    return (request->fromRequestBase(endpointId, rawJsonBody) ? PacketProcessingResult::PPR_SUCCESS : PacketProcessingResult::PPR_FAIL);
}

bool NetworkHttpPacketProcessor::createHttpResponseWithContent(const std::unique_ptr<NetworkContentResponse> &response, 
                                                               std::unique_ptr<ServerContext::HttpResponse> &httpResponse)
{
    if (!response.get())      return false;
    if (!response->isValid()) return false;
    
    boost::beast::http::status status{};
    
    if (!responseProcessingCodeToHttpCode(response->getResponseProcessingCode(), status))
        return false;
    
    httpResponse = std::make_unique<ServerContext::HttpResponse>(status, ServerContext::C_HTTP_VERSION);
    
    if (!response->getJsonBody().isEmpty()) {
        QJsonDocument jsonBodyDoc{response->getJsonBody()};
        
        if (strlen(jsonBodyDoc.toJson().data()) <= 0)
            return false;
        
        httpResponse->body() = jsonBodyDoc.toJson().data();
    }
    
    return true;
}

std::unique_ptr<ServerContext::HttpResponse> NetworkHttpPacketProcessor::createHttpResponseForBadRequest()
{
    return std::make_unique<ServerContext::HttpResponse>(boost::beast::http::status::bad_request, ServerContext::C_HTTP_VERSION);
}

bool NetworkHttpPacketProcessor::responseProcessingCodeToHttpCode(const NetworkContentResponse::ResponseProcessingCode code, 
                                                                  boost::beast::http::status &httpCode)
{
    if (code == NetworkContentResponse::ResponseProcessingCode::RPC_INVALID) return false;
    
    static const std::unordered_map<NetworkContentResponse::ResponseProcessingCode, boost::beast::http::status> responseCodeHttpCodeHash = {
        {NetworkContentResponse::ResponseProcessingCode::RPC_NOT_FOUND,      boost::beast::http::status::not_found},
        {NetworkContentResponse::ResponseProcessingCode::RPC_OK,             boost::beast::http::status::ok},
        {NetworkContentResponse::ResponseProcessingCode::RPC_ALREADY_EXISTS, boost::beast::http::status::conflict},
        {NetworkContentResponse::ResponseProcessingCode::RPC_INCORRECT_DATA, boost::beast::http::status::bad_request}
    };
    
    if (responseCodeHttpCodeHash.find(code) == responseCodeHttpCodeHash.end()) return false;
    
    httpCode = responseCodeHttpCodeHash.at(code);
    
    return true;
}

bool NetworkHttpPacketProcessor::responseToHttpContentType(const NetworkContentResponse &response,
                                                           std::string &httpContentType)
{
    httpContentType = C_DEFAULT_CONTENT_TYPE;
    
    return true;
}
