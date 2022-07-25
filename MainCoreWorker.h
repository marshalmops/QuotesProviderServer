#ifndef MAINCOREWORKER_H
#define MAINCOREWORKER_H

#include <QObject>
#include <QThread>
#include <QAbstractEventDispatcher>

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
    explicit MainCoreWorker(const uint32_t workerId,
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
    
    void recreateDatabaseFacade();
    
private:
    bool processTask(const std::unique_ptr<TaskBase> &task);
    
    //bool processSignUp();
    bool processSignIn       (const QJsonObject &jsonBody);
    bool processQuoteCreation(const QJsonObject &jsonBody);
    bool processGradeForQuote(const QJsonObject &jsonBody);
    bool processGettingHourlyQuote();
    bool processGettingDailyQuote();
    
    bool generateNewHourlyQuote();
    bool generateNewDailyQuote();
    
    bool getRandomQuote(std::unique_ptr<EntityQuote> &quote);
    
private:
    std::shared_ptr<EntityQuote> m_hourlyQuote;
    std::shared_ptr<EntityQuote> m_dailyQuote;
    
    std::unique_ptr<DatabaseFacadeBase>      m_dbFacade;
    std::unique_ptr<CoreEntityProcessorBase> m_entitiesProcessor;
    
    std::shared_ptr<ThreadedQueue<TaskBase>> m_tasksQueuePtr;
    
    uint32_t m_workerId;
    bool     m_isRunning;
};

#endif // MAINCOREWORKER_H
