#ifndef APPVIEW_H
#define APPVIEW_H

#include <QDialog>
#include <QObject>
#include <QTextEdit>

#include "Error.h"

#include "SettingsEditor.h"

class AppView : public QDialog
{
    Q_OBJECT
public:
    AppView(QWidget *parent = nullptr);
    
signals:
    // to MainCore:
    
    void errorOccured(const Error error);
    
    void unpause();
    void pause  ();
    
    void coreSettingsChanged    (std::shared_ptr<CoreSettingsBase> newCoreSettings);
    void databaseSettingsChanged(std::shared_ptr<DatabaseSettingsBase> newDatabaseSettings);    
    
public slots:
    // from MainCore:
    
    void addLogInfo(const QString logInfo);
    
    void showError(const Error error);
    void showInfo (const QString info);
    
    // from buttons:
    
    void processStart();
    void processStop ();
    void openSettings();
    
private:
    void changeControlsEnabled(bool isOnPause);
    
private:
    QTextEdit *m_logTextEdit;
    
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
};

#endif // APPVIEW_H
