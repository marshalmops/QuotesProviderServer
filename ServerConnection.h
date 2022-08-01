#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/serializer.hpp>

#include "ServerContext.h"
#include "Error.h"

using namespace boost::asio;

class ServerConnection
{
public:
    using Socket  = ip::tcp::socket;
    using Buffer  = streambuf;
    
    ServerConnection() = delete;
    ServerConnection(ServerConnection &&other);
    ServerConnection(Socket &&socket);
    ~ServerConnection() = default;
    
    // reading and writing using buffer...
    
    Error readData (std::unique_ptr<ServerContext::HttpRequest> &readData);
    Error writeData(const std::unique_ptr<ServerContext::HttpResponse> &httpDataToWrite);
    
    void close();
    
private:
    std::unique_ptr<Socket> m_socket;
    Buffer m_buffer;
};

#endif // SERVERCONNECTION_H
