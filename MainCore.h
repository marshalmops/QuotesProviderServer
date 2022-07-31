#ifndef MAINCORE_H
#define MAINCORE_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "CoreContext.h"

#include "FilesProcessor.h"

#include "Error.h"
#include "ThreadedQueue.h"

#include "MainCoreWorker.h"

class MainCore : public QObject
{
    Q_OBJECT
    
    constexpr static const uint64_t C_MSECS_IN_DAY  = 86400000;
    constexpr static const uint64_t C_MSECS_IN_HOUR = 3600000;
    
public:
    explicit MainCore(const CoreContext::Id workersCount,
                      const CoreContext::Id otherThreadsCount,
                      QObject *parent = nullptr);
    
    bool launchWorkers();
    
signals:
    // to all threads:
    
    void stopRequested();
    
    // to AppView:
    
    void logInfoGenerated(const QString logInfo);
    
    void showError(const Error error);
    void showInfo (const QString info);
    
    // to core workers:
    
    void unpauseRequested();
    void pauseRequested  ();
    
    void databaseFacadeRecreationRequested();
    
    // to server:
    
    void responseGenerated(std::shared_ptr<NetworkContentResponse> response);
    
public slots:
    // from threads:
    
    void processError(const Error err);
    
    void processThreadStop();
    
    // from timers:
    
    void changeDailyQuote ();
    void changeHourlyQuote();
    
    // from AppView:
    
    void resetCoreSettings    (const std::shared_ptr<CoreSettingsBase> newCoreSettings);
    void recreateDatabaseLayer(const std::shared_ptr<DatabaseSettingsBase> newDatabaseSettings);
    
    void unpause();
    void pause  ();
    
    void processClose();
    
    // from core workers:
    
    //void passResponseToServer(std::shared_ptr<NetworkContentResponse> response);
    
    // from server:
    
    void passRequestToWorker(std::shared_ptr<NetworkContentRequest> request);
    
private:
    void stop();
    
private:
    std::shared_ptr<ThreadedQueue<TaskBase>> m_tasksQueue;
    
    std::shared_ptr<EntityQuote> m_hourlyQuote;
    std::shared_ptr<EntityQuote> m_dailyQuote;
    
    CoreContext::Id m_workersCount;
    CoreContext::Id m_otherThreadsCount;
    
    CoreContext::Id m_stoppedThreadsCount;
    
    bool m_isClosing;
};

#endif // MAINCORE_H
