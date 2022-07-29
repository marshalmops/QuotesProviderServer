#ifndef SERVERCONTEXT_H
#define SERVERCONTEXT_H

#include <stdint.h>
#include <QString>
#include <QHash>
#include <boost/asio/ip/tcp.hpp>

namespace ServerContext {

using WorkerId   = uint32_t;
using SocketId   = uint64_t;
using EndpointId = uint32_t;
using Port       = uint16_t;

using RawData = std::string;

using Socket = boost::asio::ip::tcp::socket;

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

static const QString& getStringByEndpointId(const EndpointId endpointId) {
    if (endpointId >= Endpoints::E_COUNT || endpointId == Endpoints::E_INVALID)
        return QString{};
    
    static const QHash<EndpointId, QString> endpointsIdStringHash = {
        {E_SIGN_IN,                "SignIn"},
        {E_GET_DAILY_QUOTE,        "GetDailyQuote"},
        {E_GET_HOURLY_QUOTE,       "GetHourlyQuote"},
        {E_CREATE_QUOTE,           "CreateQuote"},
        {E_CREATE_GRADE_FOR_QUOTE, "CreateGradeForQuote"}
    };
    
    return endpointsIdStringHash.value(endpointId);
}

};

#endif // SERVERCONTEXT_H
