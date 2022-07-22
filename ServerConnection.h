#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/streambuf.hpp>

#include "ServerContext.h"

using namespace boost::asio;

class ServerConnection
{
public:
    using Socket  = ip::tcp::socket;
    using Buffer  = streambuf;
    
    ServerConnection() = delete;
    ServerConnection(Socket &&socket);
    
    // reading and writing using buffer...
    
    bool readData (ServerContext::RawData &readData);
    bool writeData(const ServerContext::RawData &dataToWrite);
    
private:
    Socket m_socket;
    Buffer m_buffer;
};

#endif // SERVERCONNECTION_H
