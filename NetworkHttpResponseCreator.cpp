#include "NetworkHttpResponseCreator.h"

bool NetworkHttpResponseCreator::createHttpResponseWithContent(NetworkContentResponse &response, 
                                                               std::string &httpResponse)
{
    if (!response.isValid()) return false;
    
    std::string responseJsonData{};
    
    response.toRawData(responseJsonData);
    
    std::string httpResponseBuffer{};
    std::ostringstream httpResponseBufferStream{httpResponseBuffer};
    
    std::string resultCodeString{};
    
    if (!responseProcessingCodeToHttpCodeString(response.getResponseProcessingCode(), resultCodeString))
        return false;
    
    std::string contentTypeString{};
    
    if (!responseToHttpContentType(response, contentTypeString))
        return false;
    
    // creating http response char*...
    
    httpResponseBufferStream << "HTTP/1.1 " << resultCodeString << std::endl;
    httpResponseBufferStream << "content-type: " << contentTypeString << std::endl;
    httpResponseBufferStream << "content-length: " << responseJsonData.length() << std::endl;
    httpResponseBufferStream << std::endl;
    httpResponseBufferStream << responseJsonData;
    
    if (httpResponseBuffer.empty()) return false;
    
    httpResponse = std::move(httpResponseBuffer);
    
    return true;
}

bool NetworkHttpResponseCreator::responseProcessingCodeToHttpCodeString(const NetworkContentResponse::ResponseProcessingCode code, 
                                                                        std::string &httpCodeString)
{
    if (code == NetworkContentResponse::ResponseProcessingCode::RPC_INVALID) return false;
    
    static const std::unordered_map<NetworkContentResponse::ResponseProcessingCode, std::string> responseCodeHttpCodeHash = {
        {NetworkContentResponse::ResponseProcessingCode::RPC_NOT_FOUND, "404 NOT FOUND"},
        {NetworkContentResponse::ResponseProcessingCode::RPC_OK,        "200 OK"}
    };
    
    if (responseCodeHttpCodeHash.find(code) == responseCodeHttpCodeHash.end()) return false;
    
    httpCodeString = responseCodeHttpCodeHash.at(code);
    
    return true;
}

bool NetworkHttpResponseCreator::responseToHttpContentType(const NetworkContentResponse &response,
                                                           std::string &httpContentType)
{
    httpContentType = C_DEFAULT_CONTENT_TYPE;
    
    return true;
}
