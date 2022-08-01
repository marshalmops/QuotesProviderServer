#include "ServerWorker.h"

ServerWorker::ServerWorker(//ThreadedQueue<ServerContext::Socket> *newClientsSocketsPtr,
                           const ServerContext::WorkerId workerId,
                           io_context *ioContextPtr,
                           ip::tcp::acceptor *acceptorPtr,
                           std::atomic_flag &isAcceptingOnQueue,
                           QObject *parent)
    : QObject{parent},
      m_workerId{workerId},
      m_responsesQueue{},
      ///m_newClientsSocketsPtr{newClientsSocketsPtr},
      m_connections{},
      m_ioContextPtr{ioContextPtr},
      m_acceptorPtr{acceptorPtr},
      m_httpPacketProcessor{std::make_unique<NetworkHttpPacketProcessor>()},
      m_isAcceptingOnQueue{isAcceptingOnQueue}, 
      m_runningFlag{true}
{
    if (workerId == 0) acceptConnectionAsync();
}

ServerWorker::~ServerWorker()
{
    qInfo() << "Worker destruction";
}

void ServerWorker::start()
{
    auto *dispatcher = QThread::currentThread()->eventDispatcher();
    
    while (m_runningFlag/*m_runningFlag.load(std::memory_order_acquire)*/) {
        dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
        
        if (!m_runningFlag) break;
        
        m_ioContextPtr->run_one_for(std::chrono::milliseconds(500));
        
        std::unique_ptr response = m_responsesQueue.takeItem();
        
        if (!response.get()) continue;
        
        std::unique_ptr<ServerContext::HttpResponse> httpResponse{};
        
        if (!m_httpPacketProcessor->createHttpResponseWithContent(response, httpResponse)) {
            emit errorOccured(Error{tr("Http response creating error!").toStdString(), true});
            
            return;
        }
        
        SlotArrayItem<ServerConnection> *socketSlotArrayItemPtr{nullptr};
        
        if (!(socketSlotArrayItemPtr = m_connections.getItem(response->getSocketId()))) {
            emit errorOccured(Error{tr("Requested socket doesn't exist!").toStdString(), true});
            
            return;
        }
        
        Error err{};
            
        if ((err = socketSlotArrayItemPtr->getValue().writeData(httpResponse)).isValid()) {
            emit errorOccured(err);
            
            return;
        }
        
        if (!m_connections.eraseItem(socketSlotArrayItemPtr->getIndex())) {
            emit errorOccured(Error{tr("Responded socket deleting error!").toStdString(), true});
            
            return;
        }
        
        if (!m_isAcceptingOnQueue.test_and_set())
            acceptConnectionAsync();
    }
}

//void ServerWorker::stop()
//{
//    m_runningFlag.store(false, std::memory_order_release);
//}

void ServerWorker::acceptConnectionAsync()
{
    m_acceptorPtr->async_accept([&](boost::system::error_code ec, ip::tcp::socket socket) {
        if (ec) {
            // error handling... boost::asio::error enum values...
            
            return;
        }
        
        ServerConnection                            newConnection  {std::move(socket)};
        std::unique_ptr<ServerContext::HttpRequest> readHttpRequest{};
        Error err{};
        
        if ((err = newConnection.readData(readHttpRequest)).isValid()) {
            emit errorOccured(err);
            
            retryAcceptConnection();
            
            return;
        }
        
        SlotArrayItem<ServerConnection> *newConnectionPtr{nullptr};
        
        if (!(newConnectionPtr = m_connections.putItem(std::move(newConnection)))) {
            emit errorOccured(Error{"New connection allocation error!", true});
            
            return;
        }
        
        std::shared_ptr<NetworkContentRequest> newRequest = std::make_shared<NetworkContentRequest>(m_workerId, newConnectionPtr->getIndex());
        
        if (!m_httpPacketProcessor->createRequestByHttpData(readHttpRequest.get(), newRequest.get())) {
            emit errorOccured(Error{"New connection allocation error!", true});                
            
            return;
        }
        
        emit requestOccured(newRequest);
        
        retryAcceptConnection();
    });
}

void ServerWorker::retryAcceptConnection()
{
    m_isAcceptingOnQueue.clear();
}

void ServerWorker::processResponse(std::shared_ptr<NetworkContentResponse> &response)
{
    m_responsesQueue.pushItem(std::make_unique<NetworkContentResponse>(std::move(*(response.get()))));
    
    response.reset();
}

void ServerWorker::stop()
{
    m_runningFlag = false;
    
    QThread::currentThread()->quit();
    
    for (auto i = 0; i < m_connections.size(); ++i) {
        auto curConnectionPtr = m_connections.getItem(i);
        
        if (!curConnectionPtr) continue;
        
        curConnectionPtr->getValue().close();
    }
            
    emit stopped();
}

//ServerContext::SocketId ServerWorker::addNewConnection(ServerConnection &&connection)
//{
    
//}
