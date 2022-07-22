QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundl

win32-g++ {
    INCLUDEPATH += C:\boost_1_66_0\boost_mingw_810\include\boost-1_66
    INCLUDEPATH += C:\Qt\Tools\OpenSSL\Win_x64\include
    LIBS += -LC:\boost_1_66_0\boost_mingw_810\lib -llibboost_system-mgw81-mt-x64-1_66
    LIBS += -LC:\Qt\Tools\OpenSSL\Win_x64\lib -llibcrypto -llibssl

    LIBS += -lws2_32
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AppInitializer.cpp \
        CoreContext.cpp \
        DatabaseContext.cpp \
        DatabaseSettingsBase.cpp \
        DatabaseSettingsContainerBase.cpp \
        DatabaseSettingsContainerEditable.cpp \
        DatabaseSettingsSQLite.cpp \
        Error.cpp \
        FilesProcessor.cpp \
        FilesProcessorGenerator.cpp \
        FilesProcessorInterface.cpp \
        FilesProcessorSettings.cpp \
        MainCore.cpp \
        MainCoreWorker.cpp \
        NetworkContentBase.cpp \
        NetworkContentRequest.cpp \
        NetworkContentResponse.cpp \
        NetworkHttpResponseCreator.cpp \
        Server.cpp \
        ServerConnection.cpp \
        ServerWorker.cpp \
        SlotArrayItem.cpp \
        SlotsArray.cpp \
        ThreadedQueue.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AppInitializer.h \
    CoreContext.h \
    DatabaseContext.h \
    DatabaseSettingsBase.h \
    DatabaseSettingsContainerBase.h \
    DatabaseSettingsContainerEditable.h \
    DatabaseSettingsSQLite.h \
    Error.h \
    FilesProcessor.h \
    FilesProcessorGenerator.h \
    FilesProcessorInterface.h \
    FilesProcessorSettings.h \
    MainCore.h \
    MainCoreWorker.h \
    NetworkContentBase.h \
    NetworkContentRequest.h \
    NetworkContentResponse.h \
    NetworkHttpResponseCreator.h \
    Server.h \
    ServerConnection.h \
    ServerContext.h \
    ServerWorker.h \
    SlotArrayItem.h \
    SlotsArray.h \
    ThreadedQueue.h
