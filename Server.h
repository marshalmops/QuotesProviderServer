#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QThread>
#include <QAbstractEventDispatcher>
#include <vector>
#include <memory>
#include <boost/asio.hpp>

#include "Error.h"
#include "ServerContext.h"
#include "ThreadedQueue.h"
#include "ServerWorker.h"

#include "NetworkContentResponse.h"
#include "NetworkContentRequest.h"

using namespace boost::asio;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(const std::string &ipString,
                    const ServerContext::Port port,
                    QObject *parent = nullptr);
    
    void start(const uint16_t workersCount);
    
protected:
    //void acceptConnectionAsync();
    void launchWorkers(const uint16_t workersCount);

signals:
    void errorOccured(const Error error);
    void networkStopped();
    
    void requestPassedToCore(std::shared_ptr<NetworkContentRequest> request);

public slots:
    void stop();
    
    void processError(const Error error);
    void processWorkerStop();
    
    void passRequestToCore   (std::shared_ptr<NetworkContentRequest> request);
    void passResponseToWorker(std::shared_ptr<NetworkContentResponse> response);

private:
    std::vector<std::shared_ptr<ServerWorker>> m_serverWorkers;
    //ThreadedQueue<ServerContext::Socket> m_newClientsSockets;
    
    io_context        m_ioContext;
    ip::tcp::acceptor m_acceptor;
    
    bool   m_isRunning;
    size_t m_networkStopCounter;
};

#endif // SERVER_H