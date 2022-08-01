#include "NetworkHttpPacketProcessor.h"

bool NetworkHttpPacketProcessor::createRequestByHttpData(const ServerContext::HttpRequest * const httpRequest,
                                                         NetworkContentRequest * const request)
{
    if (!httpRequest) return false;
    
//    boost::beast::http::parser<true, boost::beast::http::string_body> parser{};
//    boost::system::error_code err{};
    
//    parser.put(boost::asio::buffer(rawData), err);
    
//    if (err) 
//        return false;
    
//    auto parsedData = parser.get();
    
    if (httpRequest->method() != boost::beast::http::verb::post)
        return false;
    
    auto endpointPath = httpRequest->base().target();

    if (endpointPath.empty())
        return false;
    
    QString                  endpointString{QString{endpointPath.to_string().c_str()}.mid(1)};
    ServerContext::Endpoints endpointId    {ServerContext::getEndpointIdByStringHash(endpointString)};
    
    if (endpointId == ServerContext::Endpoints::E_INVALID)
        return false;
    
    auto rawJsonBody = httpRequest->body().data();
   
    return request->fromRequestBase(endpointId, rawJsonBody);
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
    
//    std::string responseJsonData{};
    
//    response.toRawData(responseJsonData);
    
//    std::string httpResponseBuffer{};
//    std::ostringstream httpResponseBufferStream{httpResponseBuffer};
    
//    std::string resultCodeString{};
    
//    if (!responseProcessingCodeToHttpCodeString(response.getResponseProcessingCode(), resultCodeString))
//        return false;
    
//    std::string contentTypeString{};
    
//    if (!responseToHttpContentType(response, contentTypeString))
//        return false;
    
//    // creating http response char*...
    
//    httpResponseBufferStream << "HTTP/1.1 " << resultCodeString << std::endl;
//    httpResponseBufferStream << "content-type: " << contentTypeString << std::endl;
//    httpResponseBufferStream << "content-length: " << responseJsonData.length() << std::endl;
//    httpResponseBufferStream << std::endl;
//    httpResponseBufferStream << responseJsonData;
    
//    if (httpResponseBuffer.empty()) return false;
    
//    httpResponse = std::move(httpResponseBuffer);
    
    return true;
}

bool NetworkHttpPacketProcessor::responseProcessingCodeToHttpCode(const NetworkContentResponse::ResponseProcessingCode code, 
                                                                  boost::beast::http::status &httpCode)
{
    if (code == NetworkContentResponse::ResponseProcessingCode::RPC_INVALID) return false;
    
    static const std::unordered_map<NetworkContentResponse::ResponseProcessingCode, boost::beast::http::status> responseCodeHttpCodeHash = {
        {NetworkContentResponse::ResponseProcessingCode::RPC_NOT_FOUND,      boost::beast::http::status::not_found},
        {NetworkContentResponse::ResponseProcessingCode::RPC_OK,             boost::beast::http::status::ok},
        {NetworkContentResponse::ResponseProcessingCode::RPC_ALREADY_EXISTS, boost::beast::http::status::conflict}
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
