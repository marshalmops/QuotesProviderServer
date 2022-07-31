#include "StringVariantMapWidget.h"

StringVariantMapWidget::StringVariantMapWidget(const QString &label, 
                                               const QMap<QString, QVariant> &prevMap, 
                                               QWidget *parent)
    : QWidget{parent},
      m_model{new StringVariantMapModel{prevMap}}
{
    QLabel *widgetLabel = new QLabel{tr(label.toStdString().c_str())};
    
    m_stringVariantMapView = new QListView{};
    
    m_stringVariantMapView->setModel(m_model);
    
    m_addStringVariantPairButton    = new QPushButton{tr("Add")};
    m_removeStringVariantPairButton = new QPushButton{tr("Remove")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addWidget(m_addStringVariantPairButton);
    buttonsLayout->addWidget(m_removeStringVariantPairButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    
    mainLayout->addWidget(widgetLabel);
    mainLayout->addWidget(m_stringVariantMapView);
    mainLayout->addLayout(buttonsLayout);
    
    connect(m_addStringVariantPairButton,    &QPushButton::clicked, this, &StringVariantMapWidget::addStringValuePair);
    connect(m_removeStringVariantPairButton, &QPushButton::clicked, this, &StringVariantMapWidget::removeCurrentItem);
}

QMap<QString, QVariant> StringVariantMapWidget::getStringVariantMap() const
{
    return m_model->getStringVariantMap();
}

void StringVariantMapWidget::addStringValuePair()
{
    std::pair<QString, QVariant> stringVariantPair{};
    StringVariantPairInputDialog inputDialog{stringVariantPair.first,
                                             stringVariantPair.second};
    
    if (inputDialog.exec() != QDialog::Accepted)
        return;
    
    Error err = m_model->addStringValuePair(stringVariantPair);
    
    if (err.isValid()) {
        emit errorOccured(err);
    
        return;
    }
    
    emit contentChanged();
}

void StringVariantMapWidget::removeCurrentItem()
{
    Error err = m_model->removeStringValuePair(m_stringVariantMapView->currentIndex());
    
    if (err.isValid()) {
        emit errorOccured(err);
    
        return;
    }
    
    emit contentChanged();
}
