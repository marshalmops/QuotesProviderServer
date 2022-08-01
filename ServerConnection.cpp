#include "ServerConnection.h"

ServerConnection::ServerConnection(Socket &&socket)
    : m_socket{std::make_unique<Socket>(std::move(socket))},
      m_buffer{}
{
    
}

ServerConnection::ServerConnection(ServerConnection &&other)
    : m_socket{other.m_socket.release()},
      m_buffer{}
{
    
}

Error ServerConnection::readData(std::unique_ptr<ServerContext::HttpRequest> &readData)
{
    if (!m_socket.get())
        return Error{"Socket does not exist!", true};
    if (!m_socket->is_open()) 
        return Error{"Socket is not open!", true};
    
    ServerContext::HttpRequest request{};
    
    boost::system::error_code err{};
    boost::beast::http::read(*m_socket, m_buffer, request, err);
            
    if (err)
        return Error{err.message(), false};
    
    readData = std::make_unique<ServerContext::HttpRequest>(std::move(request));
    
    return Error{};
}

Error ServerConnection::writeData(const std::unique_ptr<ServerContext::HttpResponse> &httpDataToWrite)
{
    if (!m_socket.get())
        return Error{"Socket does not exist!", true};
    if (!m_socket->is_open()) 
        return Error{"Socket is not open!", true};
    
    httpDataToWrite->prepare_payload();
    
    boost::beast::http::serializer<false, boost::beast::http::string_body> serializer{*dynamic_cast<boost::beast::http::message<false, boost::beast::http::string_body>*>(httpDataToWrite.get())};
    boost::system::error_code err{};
    
    boost::beast::http::write(*m_socket, serializer, err);
    
    return (err ? Error{err.message(), true} : Error{});
}

void ServerConnection::close()
{
    if (!m_socket.get()) return;
    
    if (m_socket->is_open()) {
        m_socket->close();
    }
}
