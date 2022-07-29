#include "AppInitializer.h"

bool AppInitializer::initializeApp(std::unique_ptr<AppView> &appView,
                                   std::unique_ptr<MainCore> &mainCore,
                                   std::unique_ptr<Server> &server)
{
    if (!FilesProcessor::loadSettings()) {
        createDefaultCoreSettings();
        createDefaultDatabaseSettings();
    }
    
    appView = std::make_unique<AppView>();
    
    auto totalThreadsCount = QThread::idealThreadCount();
    
    uint16_t networkWorkersCount{1};
    uint16_t coreWorkersCount   {1};
    
    if (totalThreadsCount > 1) {
        networkWorkersCount = (totalThreadsCount % 2 == 0 ? totalThreadsCount / 2 - 1 : totalThreadsCount / 2);
        coreWorkersCount    = (totalThreadsCount / 2 - 1);
    }
    
    mainCore = std::make_unique<MainCore>(coreWorkersCount, 1);
    server   = std::make_unique<Server>();
    
    // connections:
    
    // AppView -> MainCore:
    
    QObject::connect(appView.get(), &AppView::errorOccured,             mainCore.get(), &MainCore::processError);
    QObject::connect(appView.get(), &AppView::unpause,                  mainCore.get(), &MainCore::unpause);
    QObject::connect(appView.get(), &AppView::pause,                    mainCore.get(), &MainCore::pause);
    QObject::connect(appView.get(), &AppView::coreSettingsChanged,      mainCore.get(), &MainCore::resetCoreSettings);
    QObject::connect(appView.get(), &AppView::databaseSettingsChanged,  mainCore.get(), &MainCore::recreateDatabaseLayer);
    
    // MainCore -> AppView
    
    QObject::connect(mainCore.get(), &MainCore::logInfoGenerated, appView.get(), &AppView::addLogInfo);
    QObject::connect(mainCore.get(), &MainCore::showError,        appView.get(), &AppView::showError);
    QObject::connect(mainCore.get(), &MainCore::showInfo,         appView.get(), &AppView::showInfo);
    
    // Server -> MainCore:
    
    QObject::connect(server.get(), &Server::errorOccured,        mainCore.get(), &MainCore::processError,        Qt::QueuedConnection);
    QObject::connect(server.get(), &Server::networkStopped,      mainCore.get(), &MainCore::processThreadStop,   Qt::QueuedConnection);
    QObject::connect(server.get(), &Server::requestPassedToCore, mainCore.get(), &MainCore::passRequestToWorker, Qt::QueuedConnection);
    
    // MainCore -> Server:
    
    QObject::connect(mainCore.get(), &MainCore::stopRequested,     server.get(), &Server::stop,                 Qt::QueuedConnection);
    QObject::connect(mainCore.get(), &MainCore::responseGenerated, server.get(), &Server::passResponseToWorker, Qt::QueuedConnection);
    
    //
    
    QThread *networkThread = new QThread{};
    
    server->moveToThread(networkThread);
    
    QObject::connect(networkThread, &QThread::started, server.get(), [&server, networkWorkersCount](){server->start(networkWorkersCount);});
    
    networkThread->start();
    
    return mainCore->launchWorkers();
}

void AppInitializer::createDefaultCoreSettings()
{
    SettingsContainerEditable::setCoreSettings(std::make_unique<CoreSettingsBase>());
}

void AppInitializer::createDefaultDatabaseSettings()
{
    SettingsContainerEditable::setDatabaseSettings(std::make_unique<DatabaseSettingsSQLite>());
}
