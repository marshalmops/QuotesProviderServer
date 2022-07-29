#include <QApplication>

#include "AppInitializer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    std::unique_ptr<AppView>  appView{};
    std::unique_ptr<MainCore> mainCore{};
    std::unique_ptr<Server>   server  {};
    
    if (!AppInitializer::initializeApp(appView, mainCore, server)) {
        QMessageBox{QMessageBox::Icon::Critical, QObject::tr("Critical error"), QObject::tr("Initialization failed!")}.exec();
        
        return -1;
    }
    
    appView->show();

    return a.exec();
}
