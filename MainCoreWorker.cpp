#include "MainCoreWorker.h"

MainCoreWorker::MainCoreWorker(const uint32_t workerId,
                               const std::shared_ptr<ThreadedQueue<TaskBase>> &tasksQueuePtr, 
                               const std::shared_ptr<EntityQuote> &hourlyQuote,
                               const std::shared_ptr<EntityQuote> &dailyQuote,
                               QObject *parent)
    : QObject{parent},
      m_hourlyQuote{hourlyQuote},
      m_dailyQuote{dailyQuote},
      m_tasksQueuePtr{tasksQueuePtr},
      m_workerId{workerId},
      m_isRunning{false}
{
    
}

void MainCoreWorker::start()
{
    auto *dispatcher = QThread::currentThread()->eventDispatcher();
    
    m_isRunning = true;
    
    while (m_isRunning) {
        dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
        
        if (!m_isRunning) break;
        
        auto task = m_tasksQueuePtr->takeItem();
        
        if (!task.get()) continue;
        
        if (!processTask(task)) {
            emit errorOccured(Error{tr("Task processing error!").toStdString(), true});
            
            continue;
        }
    }
    
    emit stopped();
}

void MainCoreWorker::stop()
{
    m_isRunning = false;
    
    QThread::currentThread()->quit();
}

void MainCoreWorker::recreateDatabaseFacade()
{
    std::unique_ptr<DatabaseFacadeBase> newDatabaseFacade{};
    
    if (!DatabaseLayerCreator::createDatabaseFacade(QString{"connection"} + QString::number(m_workerId), newDatabaseFacade)) {
        emit errorOccured(Error{tr("Database facade recreation error!").toStdString(), true});
        
        return;
    }
        
    m_dbFacade.reset(newDatabaseFacade.release());
}

bool MainCoreWorker::processTask(const std::unique_ptr<TaskBase> &task)
{
    switch (task->getTaskType()) {
    case CoreContext::TaskType::TT_CORE_TASK: {
        TaskCore *coreTask{dynamic_cast<TaskCore*>(task.get())};
        
        if (!coreTask) return false;
        
        switch (coreTask->getCoreTaskType()) {
        case CoreContext::CoreTaskType::CTT_GET_DAILY_QUOTE:  return generateNewDailyQuote();
        case CoreContext::CoreTaskType::CTT_GET_HOURLY_QUOTE: return generateNewHourlyQuote();
        default: return false;
        }
        
        break;
    }
    case CoreContext::TaskType::TT_NETWORK_TASK: {
        TaskNetwork *networkTask{dynamic_cast<TaskNetwork*>(task.get())};
        
        if (!networkTask) return false;
        
        auto request = networkTask->getRequest();
        
        if (!request.get()) return false;
        
        switch (request->getEndpointId()) {
        case ServerContext::Endpoints::E_SIGN_IN:                return processSignIn(request->getJsonBody());
        case ServerContext::Endpoints::E_GET_DAILY_QUOTE:        return processGettingDailyQuote();
        case ServerContext::Endpoints::E_GET_HOURLY_QUOTE:       return processGettingHourlyQuote();
        case ServerContext::Endpoints::E_CREATE_QUOTE:           return processQuoteCreation(request->getJsonBody());
        case ServerContext::Endpoints::E_CREATE_GRADE_FOR_QUOTE: return processGradeForQuote(request->getJsonBody());
        }
        
        break;
    }
    default: return false;
    }
    
    return true;
}

bool MainCoreWorker::processSignIn(const QJsonObject &jsonBody)
{
    std::unique_ptr<EntityBase> userSignInData{};
    
    if (!m_entitiesProcessor->jsonToEntity(CoreContext::EntityType::ET_USER, jsonBody, userSignInData))
        return false;
    
    std::unique_ptr<EntityUser> userData{dynamic_cast<EntityUser*>(userSignInData.release())};
    
    if (!userData.get()) return false;
    
    auto coreSettings = SettingsContainerBase::getCoreSettings();
    
    QString dataForHashing {userData->getEmail() + QDateTime::currentDateTime().toString()};
    QString newSessionToken{};
    
    if (!SessionTokenGenerator::generateSessionToken(dataForHashing, coreSettings->getHashingSalt(), newSessionToken, coreSettings->getHashingAlgo()))
        return false;
    
    QDateTime curDateTime{QDateTime::currentDateTime()};
    
    std::unique_ptr<EntitySession> newSessionData{std::make_unique<EntitySession>(0, newSessionToken, curDateTime.addSecs(coreSettings->getTokenExpirationTime()), curDateTime)};
    std::unique_ptr<EntitySession> createdSession{};
    
    auto operationResultCode = m_dbFacade->createUserSession(userData, newSessionData, createdSession);
    
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
        return false;
    else if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_SUCCESS) {
        std::shared_ptr<NetworkContentResponse> response{std::make_shared<NetworkContentResponse>()}
        
        
        
        return;
    }
    
    // not found...
    
    return true;
}

bool MainCoreWorker::processQuoteCreation(const QJsonObject &jsonBody)
{
    
}

bool MainCoreWorker::processGradeForQuote(const QJsonObject &jsonBody)
{
    
}

bool MainCoreWorker::processGettingHourlyQuote()
{
    
}

bool MainCoreWorker::processGettingDailyQuote()
{
    
}

bool MainCoreWorker::generateNewHourlyQuote()
{
    std::unique_ptr<EntityQuote> newHourlyQuote{};
    
    if (!getRandomQuote(newHourlyQuote)) return false;
    
    *(m_hourlyQuote.get()) = std::move(*newHourlyQuote);
    
    return true;
}

bool MainCoreWorker::generateNewDailyQuote()
{
    std::unique_ptr<EntityQuote> newDailyQuote{};
    
    if (!getRandomQuote(newDailyQuote)) return false;
    
    *(m_dailyQuote.get()) = std::move(*newDailyQuote);
    
    return true;
}

bool MainCoreWorker::getRandomQuote(std::unique_ptr<EntityQuote> &quote)
{
    
}
