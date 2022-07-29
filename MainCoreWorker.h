#ifndef MAINCOREWORKER_H
#define MAINCOREWORKER_H

#include <QObject>
#include <QThread>
#include <QAbstractEventDispatcher>
#include <random>

#include "Error.h"

#include "NetworkContentResponse.h"

#include "CoreContext.h"
#include "ServerContext.h"

#include "ThreadedQueue.h"

#include "TaskCore.h"
#include "TaskNetwork.h"

#include "CoreEntityProcessorBase.h"

#include "DatabaseLayerCreator.h"
#include "DatabaseFacadeBase.h"

#include "SessionTokenGenerator.h"

class MainCoreWorker : public QObject
{
    Q_OBJECT
public:
    explicit MainCoreWorker(const CoreContext::Id workerId,
                            const std::shared_ptr<ThreadedQueue<TaskBase>> &tasksQueuePtr,
                            const std::shared_ptr<EntityQuote> &hourlyQuote,
                            const std::shared_ptr<EntityQuote> &dailyQuote,
                            QObject *parent = nullptr);
    
signals:
    void errorOccured(const Error err);
    
    void stopped();
    
    void requestProcessed(std::shared_ptr<NetworkContentResponse> response);
    
public slots:
    void start();
    void stop();
    
    void pause  ();
    void unpause();
    
    void recreateDatabaseFacade();
    
private:
    bool processTask(const std::unique_ptr<TaskBase> &task);
    
    //bool processSignUp();
    bool processSignIn            (const std::shared_ptr<NetworkContentRequest> &request);
    bool processQuoteCreation     (const std::shared_ptr<NetworkContentRequest> &request);
    bool processGradeForQuote     (const std::shared_ptr<NetworkContentRequest> &request);
    bool processGettingHourlyQuote(const std::shared_ptr<NetworkContentRequest> &request);
    bool processGettingDailyQuote (const std::shared_ptr<NetworkContentRequest> &request);
    
    bool checkSessionValidity(const std::unique_ptr<EntitySession> &session);
    
    bool generateTimeRelatedQuoteGettingResponse(const std::shared_ptr<NetworkContentRequest> &request,
                                                 const ServerContext::Endpoints timeRelatedQuoteEndpoint,
                                                 std::shared_ptr<NetworkContentResponse> &response);
    
    bool generateNewHourlyQuote();
    bool generateNewDailyQuote();
    
    bool getRandomQuote(std::unique_ptr<EntityQuote> &quote);
    
    bool processNoTimeRelatedQuotesCase(const std::shared_ptr<NetworkContentRequest> &request,
                                        std::shared_ptr<NetworkContentResponse> &response);
    
    void sendResponseByOperationCode(const DatabaseContext::DatabaseOperationResult result,
                                     const std::shared_ptr<NetworkContentRequest> &request,
                                     const QJsonObject &jsonBody = QJsonObject{});
    
private:
    std::shared_ptr<EntityQuote> m_hourlyQuote;
    std::shared_ptr<EntityQuote> m_dailyQuote;
    
    std::unique_ptr<DatabaseFacadeBase>      m_dbFacade;
    std::unique_ptr<CoreEntityProcessorBase> m_entitiesProcessor;
    
    std::shared_ptr<ThreadedQueue<TaskBase>> m_tasksQueuePtr;
    
    CoreContext::Id m_workerId;
    bool            m_isRunning;
    bool            m_isOnPause;
};

#endif // MAINCOREWORKER_H
