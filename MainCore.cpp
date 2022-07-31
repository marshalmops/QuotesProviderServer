#include "MainCore.h"

MainCore::MainCore(const CoreContext::Id workersCount, 
                   const CoreContext::Id otherThreadsCount, 
                   QObject *parent)
    : QObject              {parent},
      m_tasksQueue         {std::make_shared<ThreadedQueue<TaskBase>>()},
      m_hourlyQuote        {std::make_shared<EntityQuote>()},
      m_dailyQuote         {std::make_shared<EntityQuote>()},
      m_workersCount       {workersCount},
      m_otherThreadsCount  {otherThreadsCount},
      m_stoppedThreadsCount{0},
      m_isClosing{false}
{
                            
}

bool MainCore::launchWorkers()
{
    if (m_workersCount < 1) return false;
    
    for (CoreContext::Id i = 0; i < m_workersCount; ++i) {
        QThread *newThread{new QThread{}};
        
        if (!newThread) return false;
        
        MainCoreWorker *newWorker{new MainCoreWorker{i, m_tasksQueue, m_hourlyQuote, m_dailyQuote}};
    
        if (!newWorker) {
            delete newThread;
            
            return false;
        }
        
        newWorker->moveToThread(newThread);
        
        connect(newWorker, &MainCoreWorker::requestProcessed, this, &MainCore::responseGenerated, Qt::QueuedConnection);
        connect(newWorker, &MainCoreWorker::errorOccured,     this, &MainCore::processError,      Qt::QueuedConnection);
        connect(newWorker, &MainCoreWorker::stopped,          this, &MainCore::processThreadStop, Qt::QueuedConnection);
        
        connect(this, &MainCore::pauseRequested,                    newWorker, &MainCoreWorker::pause,                  Qt::QueuedConnection);
        connect(this, &MainCore::unpauseRequested,                  newWorker, &MainCoreWorker::unpause,                Qt::QueuedConnection);        
        connect(this, &MainCore::databaseFacadeRecreationRequested, newWorker, &MainCoreWorker::recreateDatabaseFacade, Qt::QueuedConnection);
        connect(this, &MainCore::stopRequested,                     newWorker, &MainCoreWorker::stop,                   Qt::QueuedConnection);
        
        connect(newThread, &QThread::started, newWorker, &MainCoreWorker::start);
        
        newThread->start();
    }
    
    // timers creation:
    
    QTimer *changeDailyQuoteTimer {new QTimer{this}};
    QTimer *changeHourlyQuoteTimer{new QTimer{this}};
    
    if (!changeDailyQuoteTimer || !changeHourlyQuoteTimer)
        return false;
    
    connect(changeDailyQuoteTimer,  &QTimer::timeout, this, &MainCore::changeDailyQuote);
    connect(changeHourlyQuoteTimer, &QTimer::timeout, this, &MainCore::changeHourlyQuote);
    
    changeDailyQuoteTimer->start(C_MSECS_IN_DAY);
    changeHourlyQuoteTimer->start(C_MSECS_IN_HOUR);
    
    return true;
}

void MainCore::processError(const Error err)
{
    if (m_isClosing) return;
    
    emit showError(err);
    
    if (!err.isCritical()) return;
    
    stop();
}

void MainCore::processThreadStop()
{
    ++m_stoppedThreadsCount;
    
    if (m_stoppedThreadsCount != (m_workersCount + m_otherThreadsCount))
        return;
    
    FilesProcessor::saveSettings();
    
    QThread::currentThread()->quit();
}

void MainCore::changeDailyQuote()
{
    emit logInfoGenerated(QString{"Daily quote change.\n\n"});
    
    m_tasksQueue->pushItem(std::make_unique<TaskCore>(CoreContext::CoreTaskType::CTT_GET_DAILY_QUOTE));
}

void MainCore::changeHourlyQuote()
{
    emit logInfoGenerated(QString{"Hourly quote change.\n\n"});
    
    m_tasksQueue->pushItem(std::make_unique<TaskCore>(CoreContext::CoreTaskType::CTT_GET_HOURLY_QUOTE));
}

void MainCore::resetCoreSettings(const std::shared_ptr<CoreSettingsBase> newCoreSettings)
{
    if (!SettingsContainerEditable::setCoreSettings(std::make_unique<CoreSettingsBase>(std::move(*(newCoreSettings.get()))))) {
        processError(Error{"Core settings updating error!", true});
        
        return;
    }
}

void MainCore::recreateDatabaseLayer(const std::shared_ptr<DatabaseSettingsBase> newDatabaseSettings)
{
    if (!DatabaseLayerCreator::createDatabaseSettingsUsingBase(std::make_unique<DatabaseSettingsBase>(std::move(*(newDatabaseSettings.get()))))) {
        processError(Error{"Database settings updating error!", true});
        
        return;
    }

    emit databaseFacadeRecreationRequested();
}

void MainCore::unpause()
{
    emit unpauseRequested();
}

void MainCore::pause()
{
    emit pauseRequested();
}

void MainCore::processClose()
{
    stop();
}

void MainCore::passRequestToWorker(std::shared_ptr<NetworkContentRequest> request)
{
    if (!request.get()) {
        processError(Error{tr("Gotten request in core doesn't exist!").toStdString(), true});
        
        return;
    }
    
    if (!request->isValid()) {
        processError(Error{tr("Gotten request in core is invalid!").toStdString(), true});
        
        return;
    }
    
    QString logData{"Endpoint: "};
    
    logData += ServerContext::getStringByEndpointId(request->getEndpointId());
    logData += QString{";\nJSON Body:\n"};
    logData += QJsonDocument{request->getJsonBody()}.toJson() + "\n\n";
    
    emit logInfoGenerated(logData);
    
    m_tasksQueue->pushItem(std::make_unique<TaskNetwork>(request));
}

void MainCore::stop()
{
    if (m_isClosing) return;
    
    m_isClosing = true;
            
    emit stopRequested();
}
