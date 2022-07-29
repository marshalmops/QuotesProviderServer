#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include "AppView.h"
#include "MainCore.h"
#include "Server.h"
#include "FilesProcessor.h"
#include "SettingsContainerEditable.h"

class AppInitializer
{
public:
    AppInitializer() = delete;

    static bool initializeApp(std::unique_ptr<AppView>  &appView,
                              std::unique_ptr<MainCore> &mainCore,
                              std::unique_ptr<Server>   &server);
    
protected:
    static void createDefaultCoreSettings    ();
    static void createDefaultDatabaseSettings();
};

#endif // APPINITIALIZER_H
