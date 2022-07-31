#include "SettingsEditor.h"

namespace {

int getHashingAlgoIndex(const QCryptographicHash::Algorithm algo) {
    int i{0};
    
    foreach (const auto &curAlgo, CoreContext::stringHashingAlgoVector) {
        if (curAlgo.second == algo) return i;
        
        ++i;
    }
    
    return -1;
}

int getDatabaseTypeIndex(const DatabaseContext::DatabaseType type) {
    int i{0};
    
    foreach (const auto &curType, DatabaseContext::stringDatabaseTypeVector) {
        if (curType.second == type) return i;
        
        ++i;
    }
    
    return -1;
}

}
SettingsEditor::SettingsEditor(QWidget *parent)
    : QDialog{parent},
      m_isCoreSettingsModified    {false},
      m_isDatabaseSettingsModified{false}
{
    // core settings:
    
    auto coreSettings = SettingsContainerBase::getCoreSettings();
    
    QLabel *hashingSaltLabel         = new QLabel{tr("Hashing salt")};
    QLabel *hashingAlgoLabel         = new QLabel{tr("Hashing algorithm")};
    QLabel *tokenExpirationTimeLabel = new QLabel{tr("Token exp. time")};
    
    QVBoxLayout *coreSettingsLabelsLayout = new QVBoxLayout{};
    
    coreSettingsLabelsLayout->addWidget(hashingSaltLabel);
    coreSettingsLabelsLayout->addWidget(hashingAlgoLabel);
    coreSettingsLabelsLayout->addWidget(tokenExpirationTimeLabel);
    
    m_hashingSaltLineEdit        = new QLineEdit{};
    m_hashingAlgoComboBox        = new QComboBox{};
    m_tokenExpirationTimeSpinBox = new QSpinBox{};
    
    m_hashingSaltLineEdit->setText(coreSettings->getHashingSalt());
    
    foreach (const auto &hashingAlgo, CoreContext::stringHashingAlgoVector)
        m_hashingAlgoComboBox->addItem(hashingAlgo.first, hashingAlgo.second);
    
    m_hashingAlgoComboBox->setCurrentIndex(getHashingAlgoIndex(coreSettings->getHashingAlgo()));
    m_tokenExpirationTimeSpinBox->setMinimum(0);
    m_tokenExpirationTimeSpinBox->setMaximum(std::numeric_limits<int>::max());
    m_tokenExpirationTimeSpinBox->setValue(coreSettings->getTokenExpirationTime());
    
    QVBoxLayout *coreSettingsInputsLayout = new QVBoxLayout{};
    
    coreSettingsInputsLayout->addWidget(m_hashingSaltLineEdit);
    coreSettingsInputsLayout->addWidget(m_hashingAlgoComboBox);
    coreSettingsInputsLayout->addWidget(m_tokenExpirationTimeSpinBox);
    
    QHBoxLayout *coreSettingsLayout = new QHBoxLayout{};
    
    coreSettingsLayout->addLayout(coreSettingsLabelsLayout);
    coreSettingsLayout->addLayout(coreSettingsInputsLayout);
    
    QWidget *coreSettingsTabWidget = new QWidget{};
    
    coreSettingsTabWidget->setLayout(coreSettingsLayout);
    
    // db settings:
    
    auto databaseSettings = SettingsContainerBase::getDatabaseSettings();
    
    QLabel *databaseTypeLabel            = new QLabel{tr("Database type")};
    QLabel *databaseUrlLabel             = new QLabel{tr("Database URL")};
    
    QVBoxLayout *databaseSettingsLabelsLayout = new QVBoxLayout{};
    
    databaseSettingsLabelsLayout->addWidget(databaseTypeLabel);
    databaseSettingsLabelsLayout->addWidget(databaseUrlLabel);
    
    m_dbTypeComboBox = new QComboBox{};
    m_dbUrlLineEdit  = new QLineEdit{};
    
    foreach (const auto &databaseType, DatabaseContext::stringDatabaseTypeVector)
        m_dbTypeComboBox->addItem(databaseType.first, databaseType.second);
    
    m_dbTypeComboBox->setCurrentIndex(getDatabaseTypeIndex(databaseSettings->getDatabaseType()));
    m_dbUrlLineEdit->setText(databaseSettings->getDatabaseUrl().toString());
    
    QVBoxLayout *databaseSettingsInputsLayout = new QVBoxLayout{};
    
    databaseSettingsInputsLayout->addWidget(m_dbTypeComboBox);
    databaseSettingsInputsLayout->addWidget(m_dbUrlLineEdit);
    
    QHBoxLayout *databaseSettingsTypeUrlLabel = new QHBoxLayout{};
    
    databaseSettingsTypeUrlLabel->addLayout(databaseSettingsLabelsLayout);
    databaseSettingsTypeUrlLabel->addLayout(databaseSettingsInputsLayout);
    
    m_additionalPropsMap = new StringVariantMapWidget{tr("Additional props"), databaseSettings->getAdditionalProps()};
    
    QVBoxLayout *databaseSettingsLayout = new QVBoxLayout{};
    
    databaseSettingsLayout->addLayout(databaseSettingsTypeUrlLabel);
    databaseSettingsLayout->addWidget(m_additionalPropsMap);
    
    QWidget *databaseSettingsTabWidget = new QWidget{};
    
    databaseSettingsTabWidget->setLayout(databaseSettingsLayout);
    
    // tabs creation:
    
    QTabWidget *settingsTabs = new QTabWidget{};
    
    settingsTabs->addTab(coreSettingsTabWidget,     tr("Core"));
    settingsTabs->addTab(databaseSettingsTabWidget, tr("Database"));
    
    // main layout:
    
    m_acceptButton = new QPushButton{tr("Accept")};
    m_cancelButton = new QPushButton{tr("Cancel")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_acceptButton);
    buttonsLayout->addWidget(m_cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    
    mainLayout->addWidget(settingsTabs);
    mainLayout->addLayout(buttonsLayout);
    
    // connects:
    
    connect(m_hashingSaltLineEdit,        &QLineEdit::textEdited,                                                this, &SettingsEditor::processCoreSettingsModificationStart);
    connect(m_hashingAlgoComboBox,        static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SettingsEditor::processCoreSettingsModificationStart);
    connect(m_tokenExpirationTimeSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),          this, &SettingsEditor::processCoreSettingsModificationStart);

    connect(m_dbTypeComboBox,     static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SettingsEditor::processDatabaseSettingsModificationStart);
    connect(m_dbUrlLineEdit,      &QLineEdit::textEdited,                                                this, &SettingsEditor::processDatabaseSettingsModificationStart);
    connect(m_additionalPropsMap, &StringVariantMapWidget::contentChanged,                               this, &SettingsEditor::processDatabaseSettingsModificationStart);  
    connect(m_additionalPropsMap, &StringVariantMapWidget::errorOccured,                                 this, &SettingsEditor::errorOccured);      
    
    connect(m_acceptButton, &QPushButton::clicked, this, &SettingsEditor::processAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
}

void SettingsEditor::processAccept()
{
    bool isConvOK{false};
    
    QCryptographicHash::Algorithm hashingAlgo = static_cast<QCryptographicHash::Algorithm>(m_hashingAlgoComboBox->currentData().toUInt(&isConvOK));
    
    if (!isConvOK) {
        closeWithError(Error{tr("Choosen hashing algo value is incorrect!").toStdString(), true});
    
        return;
    }
    
    DatabaseContext::DatabaseType databaseType = static_cast<DatabaseContext::DatabaseType>(m_dbTypeComboBox->currentData().toUInt(&isConvOK));
    
    if (!isConvOK) {
        closeWithError(Error{tr("Choosen database type value is incorrect!").toStdString(), true});
    
        return;
    }
    
    QUrl dbUrl{m_dbUrlLineEdit->text()};
    
    if (m_hashingSaltLineEdit->text().isEmpty() || m_tokenExpirationTimeSpinBox->value() <= 0
     || dbUrl.isEmpty() || !dbUrl.isValid() || databaseType == DatabaseContext::DatabaseType::DT_INVALID)
    {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is not full!"));
        
        return;
    }
    
    if (m_isCoreSettingsModified)
        if (!processCoreSettingsModification(m_hashingSaltLineEdit->text(), hashingAlgo, m_tokenExpirationTimeSpinBox->value()))
            return;
    
    if (m_isDatabaseSettingsModified)
        if (!processDatabaseSettingsModification(dbUrl, databaseType, std::forward<QMap<QString, QVariant>>(m_additionalPropsMap->getStringVariantMap())))
           return;
    
    QDialog::accept();
}

void SettingsEditor::processCoreSettingsModificationStart()
{
    if (m_isCoreSettingsModified) return;
    
    m_isCoreSettingsModified = true;
}

void SettingsEditor::processDatabaseSettingsModificationStart()
{
    if (m_isDatabaseSettingsModified) return;
    
    m_isDatabaseSettingsModified = true;
}

void SettingsEditor::closeWithError(const Error &error)
{
    emit errorOccured(error);      
    
    QDialog::close();
}

bool SettingsEditor::processCoreSettingsModification(const QString &hashingSalt,
                                                     const QCryptographicHash::Algorithm hashingAlgo,
                                                     const uint32_t tokenExpirationTime)
{
    auto newCoreSettings = std::make_shared<CoreSettingsBase>(hashingSalt,
                                                              hashingAlgo,
                                                              tokenExpirationTime);
    
    if (!newCoreSettings->isValid()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided core settings data is not correct!"));
        
        return false;
    }
    
    emit coreSettingsChanged(newCoreSettings);
    
    return true;
}

bool SettingsEditor::processDatabaseSettingsModification(const QUrl &dbUrl,
                                                         const DatabaseContext::DatabaseType dbType,
                                                         DatabaseSettingsBase::AdditionalPropsMap &&additionalProps)
{
    auto newDatabaseSettings = std::make_shared<DatabaseSettingsBase>(dbUrl,
                                                                      dbType,
                                                                      std::forward<QMap<QString, QVariant>>((additionalProps)));
    
    if (!newDatabaseSettings->isValid()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided database settings data is not correct!"));
        
        return false;
    }
    
    emit databaseSettingsChanged(newDatabaseSettings);
    
    return true;
}
