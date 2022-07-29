#include "Server.h"

Server::Server(const ServerContext::Port port,
               QObject *parent)
    : QObject{parent},
      m_ioContext{},
      m_acceptor {m_ioContext},
      m_networkStopCounter{},
      m_isRunning{false}
{
    ip::tcp::endpoint endpoint{ip::tcp::endpoint::protocol_type::v4(), port};
    
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();
    
    //acceptConnectionAsync();
    
    // workers creation...
}

void Server::start(const uint16_t workersCount)
{
    launchWorkers(workersCount);
    
    auto *eventDispatcher = QThread::currentThread()->eventDispatcher();
    boost::system::error_code error{};
    
    m_isRunning = true;
    
    while (m_isRunning) {
//        m_ioContext.run_one(error);
        
//        if (error) {
//            emit errorOccured(Error{error.message(), true});
            
//            return;
//        }
        
        eventDispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
    }
}

void Server::launchWorkers(const uint16_t workersCount)
{
    for (uint16_t i = 0; i < workersCount; ++i) {
        QThread *newThread = new QThread{};
        std::shared_ptr<ServerWorker> newWorker = std::make_shared<ServerWorker>(i, &m_ioContext, &m_acceptor);
        
        newWorker->moveToThread(newThread);
        
        connect(newThread, &QThread::started, newWorker.get(), &ServerWorker::start);
        
        connect(newWorker.get(), &ServerWorker::errorOccured,   this, &Server::errorOccured,      Qt::QueuedConnection);
        connect(newWorker.get(), &ServerWorker::stopped,        this, &Server::processWorkerStop, Qt::QueuedConnection);
        connect(newWorker.get(), &ServerWorker::requestOccured, this, &Server::passRequestToCore, Qt::QueuedConnection);
        
        m_serverWorkers.push_back(newWorker);
        newThread->start();
    }
}

void Server::stop()
{
    for (auto i = m_serverWorkers.begin(); i != m_serverWorkers.end(); ++i)
        (*i)->stop();
}

void Server::processWorkerStop()
{
    ++m_networkStopCounter;
    
    if (m_networkStopCounter != m_serverWorkers.size())
        return;
    
    m_isRunning = false;
    
    emit networkStopped();
}

//void Server::acceptConnectionAsync()
//{
//    m_acceptor.async_accept([&](boost::system::error_code ec, ip::tcp::socket socket) {
//        if (ec) {
//            // error handling...
            
//            return;
//        }
        
//        m_newClientsSockets.pushItem(std::move(socket));
        
//        acceptConnectionAsync();
//    });
//}

void Server::passRequestToCore(std::shared_ptr<NetworkContentRequest> request)
{
    emit requestPassedToCore(request);
}

void Server::passResponseToWorker(std::shared_ptr<NetworkContentResponse> response)
{
    if (m_serverWorkers.size() <= response->getWorkerId()) {
        emit errorOccured(Error{tr("Response processing worker id is incorrect!").toStdString(), true});
        
        return;
    }
    
    m_serverWorkers.at(response->getWorkerId())->processResponse(response);
}
