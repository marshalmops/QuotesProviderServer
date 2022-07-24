QT -= gui
QT += sql

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
        DatabaseDriverBase.cpp \
        DatabaseDriverSQLite.cpp \
        DatabaseDriverStandard.cpp \
        DatabaseEntityProcessorInterface.cpp \
        DatabaseEntityProcessorSQL.cpp \
        DatabaseFacadeBase.cpp \
        DatabaseFacadeStandard.cpp \
        DatabaseLayerCreator.cpp \
        DatabaseQueryBase.cpp \
        DatabaseQueryConditionBase.cpp \
        DatabaseQueryConditionStandard.cpp \
        DatabaseQueryContextStandard.cpp \
        DatabaseQueryParserInterface.cpp \
        DatabaseQueryParserResultInterface.cpp \
        DatabaseQueryParserResultSQL.cpp \
        DatabaseQueryParserStandard.cpp \
        DatabaseQueryResultBase.cpp \
        DatabaseQueryResultStandard.cpp \
        DatabaseQueryStandard.cpp \
        DatabaseQueryStandardDelete.cpp \
        DatabaseQueryStandardInsert.cpp \
        DatabaseQueryStandardSelect.cpp \
        DatabaseQueryStandardUpdate.cpp \
        DatabaseQueryUsingCondition.cpp \
        DatabaseQueryUsingValuesList.cpp \
        DatabaseSettingsBase.cpp \
        DatabaseSettingsContainerBase.cpp \
        DatabaseSettingsContainerEditable.cpp \
        DatabaseSettingsSQLite.cpp \
        EntityBase.cpp \
        EntityGrade.cpp \
        EntityQuote.cpp \
        EntitySession.cpp \
        EntityUser.cpp \
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
    DatabaseDriverBase.h \
    DatabaseDriverSQLite.h \
    DatabaseDriverStandard.h \
    DatabaseEntityProcessorInterface.h \
    DatabaseEntityProcessorSQL.h \
    DatabaseFacadeBase.h \
    DatabaseFacadeStandard.h \
    DatabaseLayerCreator.h \
    DatabaseQueryBase.h \
    DatabaseQueryConditionBase.h \
    DatabaseQueryConditionStandard.h \
    DatabaseQueryContextStandard.h \
    DatabaseQueryParserInterface.h \
    DatabaseQueryParserResultInterface.h \
    DatabaseQueryParserResultSQL.h \
    DatabaseQueryParserStandard.h \
    DatabaseQueryResultBase.h \
    DatabaseQueryResultStandard.h \
    DatabaseQueryStandard.h \
    DatabaseQueryStandardDelete.h \
    DatabaseQueryStandardInsert.h \
    DatabaseQueryStandardSelect.h \
    DatabaseQueryStandardUpdate.h \
    DatabaseQueryUsingCondition.h \
    DatabaseQueryUsingValuesList.h \
    DatabaseSettingsBase.h \
    DatabaseSettingsContainerBase.h \
    DatabaseSettingsContainerEditable.h \
    DatabaseSettingsSQLite.h \
    EntityBase.h \
    EntityGrade.h \
    EntityQuote.h \
    EntitySession.h \
    EntityUser.h \
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
