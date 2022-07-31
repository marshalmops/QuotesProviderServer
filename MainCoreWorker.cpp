#include "MainCoreWorker.h"

namespace {

CoreContext::Id getRandomId(const CoreContext::Id max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, max);
    
    return dist(rng);
}

bool getSessionTokenByJson(const QJsonObject &json,
                           CoreContext::Hash &token)
{
    if (json.isEmpty()) return false;
    if (!json.contains(EntitySession::C_TOKEN_PROP_NAME))
        return false;
    if (!json[EntitySession::C_TOKEN_PROP_NAME].isString())
        return false;
    
    CoreContext::Hash tokenBuffer{json[EntitySession::C_TOKEN_PROP_NAME].toString()};
    
    if (tokenBuffer.isEmpty()) return false;
    
    token = std::move(tokenBuffer);
    
    return true;
}

CoreContext::Hash getClearTextHash(const QString &text) {
    QString preparedText{text.toLower()};
    
    preparedText = preparedText.remove(QRegExp{"[^A-Za-zА-Яа-я]"});
    
    return QString::fromUtf8(QCryptographicHash::hash(preparedText.toUtf8(), CoreContext::C_DEFAULT_TEXT_HASHING_ALGO));
}

}

MainCoreWorker::MainCoreWorker(const CoreContext::Id workerId,
                               const std::shared_ptr<ThreadedQueue<TaskBase>> &tasksQueuePtr, 
                               const std::shared_ptr<EntityQuote> &hourlyQuote,
                               const std::shared_ptr<EntityQuote> &dailyQuote,
                               QObject *parent)
    : QObject{parent},
      m_hourlyQuote{hourlyQuote},
      m_dailyQuote{dailyQuote},
      m_dbFacade{nullptr},
      m_entitiesProcessor{nullptr},
      m_tasksQueuePtr{tasksQueuePtr},
      m_workerId{workerId},
      m_isRunning{false},
      m_isOnPause{false}
{
    
}

void MainCoreWorker::start()
{
    auto *dispatcher = QThread::currentThread()->eventDispatcher();
    
    m_isRunning = true;
    
    while (m_isRunning) {
        dispatcher->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
        
        if (m_isOnPause)  continue;
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

void MainCoreWorker::pause()
{
    m_isOnPause = true;
}

void MainCoreWorker::unpause()
{
    m_isOnPause = false;
}

void MainCoreWorker::recreateDatabaseFacade()
{
    std::unique_ptr<DatabaseFacadeBase> newDatabaseFacade{};
    
    if (!DatabaseLayerCreator::createDatabaseFacade(QString{"connection"} + QString::number(m_workerId), newDatabaseFacade)) {
        emit errorOccured(Error{tr("Database facade recreation error!").toStdString(), true});
        
        return;
    }
    
    if (m_dbFacade.get())
        m_dbFacade.reset(newDatabaseFacade.release());
    else
        m_dbFacade = std::move(newDatabaseFacade);
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
        
        if (!networkTask)            return false;
        if (!networkTask->isValid()) return false;
        
        auto request = networkTask->getRequest();
        
        switch (request->getEndpointId()) {
        case ServerContext::Endpoints::E_SIGN_IN:                return processSignIn(request);
        case ServerContext::Endpoints::E_GET_DAILY_QUOTE:        return processGettingDailyQuote(request);
        case ServerContext::Endpoints::E_GET_HOURLY_QUOTE:       return processGettingHourlyQuote(request);
        case ServerContext::Endpoints::E_CREATE_QUOTE:           return processQuoteCreation(request);
        case ServerContext::Endpoints::E_CREATE_GRADE_FOR_QUOTE: return processGradeForQuote(request);
        }
        
        break;
    }
    default: return false;
    }
    
    return true;
}

bool MainCoreWorker::processSignIn(const std::shared_ptr<NetworkContentRequest> &request)
{
    std::unique_ptr<EntityBase> userSignInData{};
    
    if (!m_entitiesProcessor->jsonToEntity(CoreContext::EntityType::ET_USER, request->getJsonBody(), userSignInData))
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
    
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_SUCCESS) {
        QJsonObject sessionDataJson{};
        
        if (!m_entitiesProcessor->entityToJSON(createdSession.get(), sessionDataJson))
            return false;
        if (sessionDataJson.isEmpty()) return false;
        
        sendResponseByOperationCode(operationResultCode, request, sessionDataJson);
        
    } else
        sendResponseByOperationCode(operationResultCode, request);
    
    return true;
}

bool MainCoreWorker::processQuoteCreation(const std::shared_ptr<NetworkContentRequest> &request)
{
    auto jsonBody = request->getJsonBody();
    
    std::unique_ptr<EntityBase> quoteDataBase{};
    
    if (!m_entitiesProcessor->jsonToEntity(CoreContext::EntityType::ET_QUOTE, jsonBody, quoteDataBase))
        return false;
    
    std::unique_ptr<EntityQuote> quoteDataRaw{dynamic_cast<EntityQuote*>(quoteDataBase.release())};
    
    CoreContext::Hash quoteHash{getClearTextHash(quoteDataRaw->getText())};
    
    if (quoteHash.isEmpty()) return false;
    
    std::unique_ptr<EntityQuote> quoteData{std::make_unique<EntityQuote>(quoteDataRaw->getText(), quoteDataRaw->getAuthor(), quoteHash)};
    
    if (!quoteData.get()) return false;
    
    CoreContext::Hash sessionToken{};
    
    if (!getSessionTokenByJson(jsonBody, sessionToken))
        return false;
    
    std::unique_ptr<EntitySession> session{};
    
    auto operationResultCode = m_dbFacade->getSessionByToken(sessionToken, session);
    
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
        return false;
    else if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND) {
        sendResponseByOperationCode(operationResultCode, request);
    }
    
    if (!session->isValid()) return false;
    if (!checkSessionValidity(session)) {
        operationResultCode = m_dbFacade->removeSessionByToken(sessionToken);
        
        if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
            return false;
        
        sendResponseByOperationCode(operationResultCode, request);
        
        return true;
    }
    
    std::unique_ptr<EntityQuote> createdQuote{};
    
    operationResultCode = m_dbFacade->createQuote(session, quoteData, createdQuote);
    
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
        return false;
    
    sendResponseByOperationCode(operationResultCode, request);
    
    return true;
}

bool MainCoreWorker::processGradeForQuote(const std::shared_ptr<NetworkContentRequest> &request)
{
    std::unique_ptr<EntityBase> gradeDataBase{};
    
    if (!m_entitiesProcessor->jsonToEntity(CoreContext::EntityType::ET_GRADE, request->getJsonBody(), gradeDataBase))
        return false;
    
    std::unique_ptr<EntityGrade> gradeData{dynamic_cast<EntityGrade*>(gradeDataBase.release())};
    
    if (!gradeData.get()) return false;
    
    std::unique_ptr<EntityGrade> createdGrade{};
    
    auto operationResultCode = m_dbFacade->createGradeForQuote(gradeData, createdGrade);
    
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
        return false;
    
    sendResponseByOperationCode(operationResultCode, request);
    
    return true;
}

bool MainCoreWorker::processGettingHourlyQuote(const std::shared_ptr<NetworkContentRequest> &request)
{
    std::shared_ptr<NetworkContentResponse> response{};
    
    if (!generateTimeRelatedQuoteGettingResponse(request, ServerContext::Endpoints::E_GET_HOURLY_QUOTE, response))
        return false;
    
    if (!request.get()) return false;
    
    emit requestProcessed(response);
    
    return true;
}

bool MainCoreWorker::processGettingDailyQuote(const std::shared_ptr<NetworkContentRequest> &request)
{
    std::shared_ptr<NetworkContentResponse> response{};
    
    if (!generateTimeRelatedQuoteGettingResponse(request, ServerContext::Endpoints::E_GET_DAILY_QUOTE, response))
        return false;
    
    if (!request.get()) return false;
    
    emit requestProcessed(response);
    
    return true;
}

bool MainCoreWorker::checkSessionValidity(const std::unique_ptr<EntitySession> &session)
{
    return (QDateTime::currentDateTime() < session->getExpirationDateTime());
}

bool MainCoreWorker::generateTimeRelatedQuoteGettingResponse(const std::shared_ptr<NetworkContentRequest> &request, 
                                                             const ServerContext::Endpoints timeRelatedQuoteEndpoint,
                                                             std::shared_ptr<NetworkContentResponse> &response)
{
    std::unique_ptr<EntityQuote> curTimeRelatedQuote{};
    
    switch (timeRelatedQuoteEndpoint) {
    case ServerContext::Endpoints::E_GET_HOURLY_QUOTE: {
        if (!m_hourlyQuote.get())
            return processNoTimeRelatedQuotesCase(request, response);
        
        curTimeRelatedQuote = std::make_unique<EntityQuote>(*m_hourlyQuote);
        
        break;
    }
    case ServerContext::Endpoints::E_GET_DAILY_QUOTE:  {
        if (!m_dailyQuote.get())
            return processNoTimeRelatedQuotesCase(request, response);
        
        curTimeRelatedQuote = std::make_unique<EntityQuote>(*m_dailyQuote);  
        
        break;
    }
    default: return false;
    }
    
    if (!curTimeRelatedQuote.get()) return false;
    
    QJsonObject quoteJson{};
    
    if (!m_entitiesProcessor->entityToJSON(curTimeRelatedQuote.get(), quoteJson))
        return false;
    if (quoteJson.isEmpty()) return false;
    
    response = std::make_shared<NetworkContentResponse>(request->getWorkerId(),
                                                        request->getSocketId(),
                                                        NetworkContentResponse::ResponseProcessingCode::RPC_OK,
                                                        quoteJson);
    
    return true;
}

bool MainCoreWorker::generateNewHourlyQuote()
{
    std::unique_ptr<EntityQuote> newHourlyQuote{};
    
    if (!getRandomQuote(newHourlyQuote)) return false;
    if (!newHourlyQuote.get())           return true;
    
    *(m_hourlyQuote.get()) = std::move(*newHourlyQuote);
    
    return true;
}

bool MainCoreWorker::generateNewDailyQuote()
{
    std::unique_ptr<EntityQuote> newDailyQuote{};
    
    if (!getRandomQuote(newDailyQuote)) return false;
    if (!newDailyQuote.get())           return true;
    
    *(m_dailyQuote.get()) = std::move(*newDailyQuote);
    
    return true;
}

bool MainCoreWorker::getRandomQuote(std::unique_ptr<EntityQuote> &quote)
{
    CoreContext::Id quotesMaxId{};
    
    auto operationResultCode = m_dbFacade->getQuotesCount(quotesMaxId);
    
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
        return false;
    if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND)
        return true;
    
    // from 1 to...
    
    std::unique_ptr<EntityQuote> randomQuote{};
    
    while (true) {
        auto randomQuoteId = getRandomId(quotesMaxId);
        
        operationResultCode = m_dbFacade->getQuoteById(randomQuoteId, randomQuote);
        
        if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_ERROR)
            return false;
        if (operationResultCode == DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND)
            continue;
        
        break;
    }
    
    if (!randomQuote.get()) return false;
    
    quote = std::unique_ptr<EntityQuote>(randomQuote.release());
    
    return true;
}

bool MainCoreWorker::processNoTimeRelatedQuotesCase(const std::shared_ptr<NetworkContentRequest> &request,
                                                    std::shared_ptr<NetworkContentResponse> &response)
{
    response = std::make_shared<NetworkContentResponse>(request->getWorkerId(),
                                                        request->getSocketId(),
                                                        NetworkContentResponse::ResponseProcessingCode::RPC_NOT_FOUND);
    
    return true;
}

void MainCoreWorker::sendResponseByOperationCode(const DatabaseContext::DatabaseOperationResult result,
                                                 const std::shared_ptr<NetworkContentRequest> &request,
                                                 const QJsonObject &jsonBody)
{
    std::shared_ptr<NetworkContentResponse>        response   {};
    NetworkContentResponse::ResponseProcessingCode networkCode{};
    
    switch (result) {
    case DatabaseContext::DatabaseOperationResult::DOR_SUCCESS:        {networkCode = NetworkContentResponse::ResponseProcessingCode::RPC_OK;             break;}
    case DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND:      {networkCode = NetworkContentResponse::ResponseProcessingCode::RPC_NOT_FOUND;      break;}
    case DatabaseContext::DatabaseOperationResult::DOR_ALREADY_EXISTS: {networkCode = NetworkContentResponse::ResponseProcessingCode::RPC_ALREADY_EXISTS; break;}
    }
    
    response = std::make_shared<NetworkContentResponse>(request->getWorkerId(),
                                                        request->getSocketId(),
                                                        networkCode,
                                                        jsonBody);
    
    emit requestProcessed(response);
}
