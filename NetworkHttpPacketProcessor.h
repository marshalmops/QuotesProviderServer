#ifndef NETWORKHTTPPACKETPROCESSOR_H
#define NETWORKHTTPPACKETPROCESSOR_H

#include <unordered_map>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/logic/tribool.hpp>

#include "ServerContext.h"

#include "NetworkContentResponse.h"
#include "NetworkContentRequest.h"

class NetworkHttpPacketProcessor
{
    constexpr static const char* C_DEFAULT_CONTENT_TYPE = "application/json";
    
public:
    enum PacketProcessingResult {
        PPR_FAIL = 0,
        PPR_SUCCESS,
        PPR_INCORRECT_DATA
    };
    
    NetworkHttpPacketProcessor() = default;
    
    PacketProcessingResult createRequestByHttpData(const ServerContext::HttpRequest *const httpRequest,
                                                  NetworkContentRequest *const request);
    bool createHttpResponseWithContent(const std::unique_ptr<NetworkContentResponse> &response,
                                       std::unique_ptr<ServerContext::HttpResponse> &httpResponse);
    
    std::unique_ptr<ServerContext::HttpResponse> createHttpResponseForBadRequest();
    
protected:
    bool responseProcessingCodeToHttpCode(const NetworkContentResponse::ResponseProcessingCode code, 
                                          boost::beast::http::status &httpCode);
    bool responseToHttpContentType(const NetworkContentResponse &response,
                                   std::string &httpContentType);
};

#endif // NETWORKHTTPPACKETPROCESSOR_H
