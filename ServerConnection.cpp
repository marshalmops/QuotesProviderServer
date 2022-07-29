#include "ServerConnection.h"

ServerConnection::ServerConnection(Socket &&socket)
    : m_socket{std::move(socket)},
      m_buffer{}
{
    
}

ServerConnection::ServerConnection(ServerConnection &&other)
    : m_socket{std::move(other.m_socket)},
      m_buffer{}
{
    
}

bool ServerConnection::readData(ServerContext::RawData &readData)
{
    if (!m_socket.is_open()) return false;
    
    auto readBytesCount = read_until(m_socket, m_buffer, '\n');
    
    if (readBytesCount <= 0) return false;
    
    std::istream readStream{&m_buffer};
    
    readStream >> readData;
    
    m_buffer.commit(readBytesCount);
    
    return true;
}

bool ServerConnection::writeData(const ServerContext::RawData &dataToWrite)
{
    if (!m_socket.is_open() || dataToWrite.empty()) return false;
    
    std::ostream writeStream{&m_buffer};
    
    writeStream << dataToWrite;
    
    auto writtenBytesCount = write(m_socket, m_buffer);
    
    if (writtenBytesCount <= 0) return false;
    
    m_buffer.consume(writtenBytesCount);
    
    return true;
}
