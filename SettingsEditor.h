#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H

#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QTabWidget>
#include <QSpinBox>
#include <limits>

#include "CoreContext.h"
#include "DatabaseContext.h"

#include "StringVariantMapWidget.h"

#include "SettingsContainerBase.h"

class SettingsEditor : public QDialog
{
    Q_OBJECT
public:
    SettingsEditor(QWidget *parent = nullptr);
    
public slots:
    // from buttons:
    
    void processAccept();
    
    // from local inputs:
    
    void processCoreSettingsModificationStart();
    void processDatabaseSettingsModificationStart();
    
signals:
    // to AppView:
    
    void errorOccured(const Error error);
    
    void coreSettingsChanged    (std::shared_ptr<CoreSettingsBase> newCoreSettings);
    void databaseSettingsChanged(std::shared_ptr<DatabaseSettingsBase> newDatabaseSettings);
    
private:
    void closeWithError(const Error &error);
    
    bool processCoreSettingsModification(const QString &hashingSalt,
                                         const QCryptographicHash::Algorithm hashingAlgo,
                                         const uint32_t tokenExpirationTime);
    bool processDatabaseSettingsModification(const QUrl &dbUrl,
                                             const DatabaseContext::DatabaseType dbType,
                                             DatabaseSettingsBase::AdditionalPropsMap &&additionalProps);
    
private:
    QLineEdit *m_hashingSaltLineEdit;
    QComboBox *m_hashingAlgoComboBox;
    QSpinBox  *m_tokenExpirationTimeSpinBox;
    
    QComboBox              *m_dbTypeComboBox;
    QLineEdit              *m_dbUrlLineEdit;
    StringVariantMapWidget *m_additionalPropsMap;
    
    QPushButton *m_acceptButton;
    QPushButton *m_cancelButton;
    
    bool m_isCoreSettingsModified;
    bool m_isDatabaseSettingsModified;
};

#endif // SETTINGSEDITOR_H
