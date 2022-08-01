#ifndef NETWORKHTTPPACKETPROCESSOR_H
#define NETWORKHTTPPACKETPROCESSOR_H

#include <unordered_map>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/string_body.hpp>

#include "ServerContext.h"

#include "NetworkContentResponse.h"
#include "NetworkContentRequest.h"

class NetworkHttpPacketProcessor
{
    constexpr static const char* C_DEFAULT_CONTENT_TYPE = "application/json";
    
public:
    NetworkHttpPacketProcessor() = default;
    
    bool createRequestByHttpData(const ServerContext::HttpRequest *const httpRequest,
                                NetworkContentRequest *const request);
    bool createHttpResponseWithContent(const std::unique_ptr<NetworkContentResponse> &response,
                                       std::unique_ptr<ServerContext::HttpResponse> &httpResponse);
    
protected:
    bool responseProcessingCodeToHttpCode(const NetworkContentResponse::ResponseProcessingCode code, 
                                          boost::beast::http::status &httpCode);
    bool responseToHttpContentType(const NetworkContentResponse &response,
                                   std::string &httpContentType);
};

#endif // NETWORKHTTPPACKETPROCESSOR_H
