#ifndef SERVERCONTEXT_H
#define SERVERCONTEXT_H

#include <stdint.h>
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
    E_SIGN_UP,
    E_SIGN_IN,
    E_GET_DAILY_QUOTE,
    E_GET_HOURLY_QUOTE,
    E_CREATE_QUOTE
};
};

#endif // SERVERCONTEXT_H
