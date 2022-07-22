#ifndef NETWORKHTTPRESPONSECREATOR_H
#define NETWORKHTTPRESPONSECREATOR_H

#include <unordered_map>

#include "NetworkContentResponse.h"

class NetworkHttpResponseCreator
{
    constexpr static const char* C_DEFAULT_CONTENT_TYPE = "application/json";
    
public:
    NetworkHttpResponseCreator() = default;
    
    bool createHttpResponseWithContent(NetworkContentResponse &response,
                                       std::string &httpResponse);
    
protected:
    bool responseProcessingCodeToHttpCodeString(const NetworkContentResponse::ResponseProcessingCode code,
                                                std::string &httpCodeString);
    bool responseToHttpContentType(const NetworkContentResponse &response,
                                   std::string &httpContentType);
};

#endif // NETWORKHTTPRESPONSECREATOR_H
