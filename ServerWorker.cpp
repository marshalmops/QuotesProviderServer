#include "ServerWorker.h"

ServerWorker::ServerWorker(//ThreadedQueue<ServerContext::Socket> *newClientsSocketsPtr,
                           const ServerContext::WorkerId workerId,
                           io_context *ioContextPtr,
                           ip::tcp::acceptor *acceptorPtr,
                           QObject *parent)
    : QObject{parent},
      m_responsesQueue{},
      ///m_newClientsSocketsPtr{newClientsSocketsPtr},
      m_connections{},
      m_ioContextPtr{ioContextPtr},
      m_acceptorPtr{acceptorPtr},
      m_httpResponseCreator{std::make_unique<NetworkHttpResponseCreator>()}
    //, m_runningFlag{true}
{
    if (workerId == 0) acceptConnectionAsync();
}

void ServerWorker::start()
{
    while (m_ioContextPtr->run_one()/*m_runningFlag.load(std::memory_order_acquire)*/) {
        
//        if (error) {
//            emit errorOccured(Error{error.message(), true});
            
//            return;
//        }
        
        std::unique_ptr response = m_responsesQueue.takeItem();
        
        if (!response.get()) continue;
        
        std::string httpResponse{};
        
        if (!m_httpResponseCreator->createHttpResponseWithContent(*response, httpResponse)) {
            emit errorOccured(Error{tr("Http response creating error!").toStdString(), true});
            
            return;
        }
        
        SlotArrayItem<ServerConnection> *socketSlotArrayItemPtr;
        
        if (!(socketSlotArrayItemPtr = m_connections.getItem(response->getSocketId()))) {
            emit errorOccured(Error{tr("Requested socket doesn't exist!").toStdString(), true});
            
            return;
        }
            
        if (!socketSlotArrayItemPtr->getValue().writeData(httpResponse)) {
            emit errorOccured(Error{tr("Response sending error!").toStdString(), true});
            
            return;
        }
        
        if (!m_connections.eraseItem(socketSlotArrayItemPtr->getIndex())) {
            emit errorOccured(Error{tr("Responded socket deleting error!").toStdString(), true});
            
            return;
        }
    }
    
    emit stopped();
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
        
        ServerConnection       newConnection{std::move(socket)};
        ServerContext::RawData readData     {};
        
        newConnection.readData(readData);
        
        if (readData.empty()) {
            emit errorOccured(Error{"No data has gotten", false});
            
        } else {
            SlotArrayItem<ServerConnection> *newConnectionPtr{nullptr};
            
            if (!(newConnectionPtr = m_connections.putItem(std::move(newConnection)))) {
                emit errorOccured(Error{"New connection allocation error!", true});
            
                return;
            }
            
            std::shared_ptr<NetworkContentRequest> newRequest = std::make_shared<NetworkContentRequest>(m_workerId, newConnectionPtr->getIndex());
            
            if (!newRequest->fromRawData(readData)) {
                emit errorOccured(Error{"New connection allocation error!", true});                
           
                return;
            }
            
            emit requestOccured(newRequest);
        }
        
        acceptConnectionAsync();
    });
}

void ServerWorker::processResponse(std::shared_ptr<NetworkContentResponse> &response)
{
    m_responsesQueue.pushItem(std::make_unique<NetworkContentResponse>(std::move(*(response.get()))));
    
    response.reset();
}

//ServerContext::SocketId ServerWorker::addNewConnection(ServerConnection &&connection)
//{
    
//}
