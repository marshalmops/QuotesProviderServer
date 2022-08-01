#ifndef SERVERCONTEXT_H
#define SERVERCONTEXT_H

#include <boost/beast/http.hpp>
#include <stdint.h>
#include <QString>
#include <QHash>
#include <boost/asio/ip/tcp.hpp>

namespace ServerContext {

using WorkerId   = uint32_t;
using SocketId   = uint64_t;
using EndpointId = uint32_t;
using Port       = uint16_t;

using HttpRequest  = boost::beast::http::request<boost::beast::http::string_body>;
using HttpResponse = boost::beast::http::response<boost::beast::http::string_body>;

using RawData = std::string;

using Socket = boost::asio::ip::tcp::socket;

constexpr static const unsigned C_HTTP_VERSION = 11;

enum Endpoints : EndpointId {
    E_INVALID = 0,
    //E_SIGN_UP,
    E_SIGN_IN,
    E_GET_DAILY_QUOTE,
    E_GET_HOURLY_QUOTE,
    E_CREATE_QUOTE,
    E_CREATE_GRADE_FOR_QUOTE,
    E_COUNT
};

static const QHash<EndpointId, QString>& getEndpointStringHash() {
    static const QHash<EndpointId, QString> endpointsIdStringHash = {
        {E_SIGN_IN,                "signin"},
        {E_GET_DAILY_QUOTE,        "getdailyquote"},
        {E_GET_HOURLY_QUOTE,       "gethourlyquote"},
        {E_CREATE_QUOTE,           "createquote"},
        {E_CREATE_GRADE_FOR_QUOTE, "creategradeforquote"}
    };
    
    return endpointsIdStringHash;
}

static const QString getStringByEndpointId(const EndpointId endpointId) {
    if (endpointId >= Endpoints::E_COUNT || endpointId == Endpoints::E_INVALID)
        return QString{};
    
    return getEndpointStringHash().value(endpointId);
}

static const EndpointId getEndpointIdByStringHash(const QString &endpointString) {
    if (endpointString.isEmpty()) return false;
    
    EndpointId endpointId{getEndpointStringHash().key(endpointString)};
    
    return ((endpointId >= Endpoints::E_COUNT || endpointId <= Endpoints::E_INVALID)
           ? Endpoints::E_INVALID : endpointId);
}

};

#endif // SERVERCONTEXT_H
