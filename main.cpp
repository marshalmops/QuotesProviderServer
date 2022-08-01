#include <QApplication>

#include "AppInitializer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    a.setQuitOnLastWindowClosed(false);
    
    std::unique_ptr<AppView>  appView {};
    std::unique_ptr<MainCore> mainCore{};
    std::unique_ptr<Server>   server  {};
    
    qRegisterMetaType<Error>();
    qRegisterMetaType<std::shared_ptr<NetworkContentRequest>>();
    qRegisterMetaType<std::shared_ptr<NetworkContentResponse>>();
    qRegisterMetaType<std::shared_ptr<CoreSettingsBase>>();
    qRegisterMetaType<std::shared_ptr<DatabaseSettingsBase>>();
    
    if (!AppInitializer::initializeApp(appView, mainCore, server)) {
        QMessageBox{QMessageBox::Icon::Critical, QObject::tr("Critical error"), QObject::tr("Initialization failed!")}.exec();
        
        return -1;
    }
    
    appView->show();

    return a.exec();
}
