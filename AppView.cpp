#include "AppView.h"

AppView::AppView(QWidget *parent)
    : QDialog{parent}
{
    QLabel *logLabel = new QLabel{tr("Log")};
    
    m_logTextEdit = new QTextEdit{};
    
    QVBoxLayout *logLayout = new QVBoxLayout{};
    
    logLayout->addWidget(logLabel);
    logLayout->addWidget(m_logTextEdit);
    
    m_startButton = new QPushButton{tr("Start")};
    m_stopButton  = new QPushButton{tr("Stop")};
    
    QPushButton *settingsButton = new QPushButton{tr("Settings")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_startButton);
    buttonsLayout->addWidget(m_stopButton);
    buttonsLayout->addWidget(settingsButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    
    mainLayout->addLayout(logLayout);
    mainLayout->addLayout(buttonsLayout);
    
    connect(m_startButton,  &QPushButton::clicked, this, &AppView::processStart);
    connect(m_stopButton,   &QPushButton::clicked, this, &AppView::processStop);
    connect(settingsButton, &QPushButton::clicked, this, &AppView::openSettings);
    
    changeControlsEnabled(false);
}

void AppView::addLogInfo(const QString logInfo)
{
    m_logTextEdit->append(logInfo);
}

void AppView::showError(const Error error)
{
    QMessageBox::warning(this, tr("Error"), error.getText().c_str());
}

void AppView::showInfo(const QString info)
{
    QMessageBox::information(this, tr("Info"), info);
}

void AppView::processStart()
{
    changeControlsEnabled(false);
    
    emit unpause();
}

void AppView::processStop()
{
    changeControlsEnabled(true);
    
    emit pause();
}

void AppView::openSettings()
{
    SettingsEditor settingsEditor{this};
    
    connect(&settingsEditor, &SettingsEditor::errorOccured,            this, &AppView::errorOccured);
    connect(&settingsEditor, &SettingsEditor::coreSettingsChanged,     this, &AppView::coreSettingsChanged);
    connect(&settingsEditor, &SettingsEditor::databaseSettingsChanged, this, &AppView::databaseSettingsChanged);
    
    settingsEditor.exec();
}

void AppView::changeControlsEnabled(bool isOnPause)
{
    m_startButton->setEnabled(isOnPause);
    m_stopButton->setEnabled(!isOnPause);
}
