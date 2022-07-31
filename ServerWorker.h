#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <vector>
#include <atomic>
#include <boost/asio/ip/tcp.hpp>

#include "ServerContext.h"

#include "ThreadedQueue.h"
#include "SlotsArray.h"
#include "ServerConnection.h"

#include "NetworkHttpResponseCreator.h"

#include "NetworkContentResponse.h"
#include "NetworkContentRequest.h"

#include "Error.h"

using namespace boost::asio;

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    ServerWorker() = delete;
    ServerWorker(const ServerContext::WorkerId workerId,
                 io_context *ioContextPtr,
                 ip::tcp::acceptor *acceptorPtr,
                 //ThreadedQueue<ServerContext::Socket>* newClientsSocketsPtr,
                 QObject *parent = nullptr);
    
    void start();
    //void stop();
    
    void processResponse(std::shared_ptr<NetworkContentResponse> &response);
    
protected:
    void acceptConnectionAsync();
    //ServerContext::SocketId addNewConnection(ServerConnection &&connection);
    
signals:
    void errorOccured(const Error error);
    void stopped();
    
    void requestOccured(std::shared_ptr<NetworkContentRequest> request);
    
private:
    ThreadedQueue<NetworkContentResponse> m_responsesQueue;
    //ThreadedQueue<ServerContext::Socket>* m_newClientsSocketsPtr;
    
    SlotsArray<ServerConnection> m_connections;
    
    ServerContext::WorkerId m_workerId;
    
    io_context        *m_ioContextPtr;
    ip::tcp::acceptor *m_acceptorPtr;
    
    std::unique_ptr<NetworkHttpResponseCreator> m_httpResponseCreator;
    
    //std::atomic<bool> m_runningFlag;
};

#endif // SERVERWORKER_H
