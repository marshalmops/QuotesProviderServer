QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundl

win32-g++ {
    INCLUDEPATH += C:\boost_1_66_0\boost_mingw_810\include\boost-1_66
    INCLUDEPATH += C:\Qt\Tools\OpenSSL\Win_x64\include
    LIBS += -LC:\boost_1_66_0\boost_mingw_810\lib -llibboost_system-mgw81-mt-x64-1_66 -lwsock32
    LIBS += -LC:\Qt\Tools\OpenSSL\Win_x64\lib -llibcrypto -llibssl

    LIBS += -lws2_32
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AppInitializer.cpp \
        AppView.cpp \
        CoreContext.cpp \
        CoreEntityProcessorBase.cpp \
        CoreSettingsBase.cpp \
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
        DatabaseSettingsSQLite.cpp \
        EntityBase.cpp \
        EntityGrade.cpp \
        EntityQuote.cpp \
        EntitySession.cpp \
        EntityUser.cpp \
        Error.cpp \
        FilesProcessor.cpp \
        FilesProcessorSettings.cpp \
        MainCore.cpp \
        MainCoreWorker.cpp \
        NetworkContentBase.cpp \
        NetworkContentRequest.cpp \
        NetworkContentResponse.cpp \
        NetworkHttpPacketProcessor.cpp \
        Server.cpp \
        ServerConnection.cpp \
        ServerWorker.cpp \
        SessionTokenGenerator.cpp \
        SettingsContainerBase.cpp \
        SettingsContainerEditable.cpp \
        SettingsEditor.cpp \
        SettingsInterface.cpp \
        SlotArrayItem.cpp \
        SlotsArray.cpp \
        StringVariantMapModel.cpp \
        StringVariantMapWidget.cpp \
        StringVariantPairInputDialog.cpp \
        TaskBase.cpp \
        TaskCore.cpp \
        TaskNetwork.cpp \
        ThreadedQueue.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AppInitializer.h \
    AppView.h \
    CoreContext.h \
    CoreEntityProcessorBase.h \
    CoreSettingsBase.h \
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
    DatabaseSettingsSQLite.h \
    EntityBase.h \
    EntityGrade.h \
    EntityQuote.h \
    EntitySession.h \
    EntityUser.h \
    Error.h \
    FilesProcessor.h \
    FilesProcessorSettings.h \
    MainCore.h \
    MainCoreWorker.h \
    NetworkContentBase.h \
    NetworkContentRequest.h \
    NetworkContentResponse.h \
    NetworkHttpPacketProcessor.h \
    Server.h \
    ServerConnection.h \
    ServerContext.h \
    ServerWorker.h \
    SessionTokenGenerator.h \
    SettingsContainerBase.h \
    SettingsContainerEditable.h \
    SettingsEditor.h \
    SettingsInterface.h \
    SlotArrayItem.h \
    SlotsArray.h \
    StringVariantMapModel.h \
    StringVariantMapWidget.h \
    StringVariantPairInputDialog.h \
    TaskBase.h \
    TaskCore.h \
    TaskNetwork.h \
    ThreadedQueue.h
