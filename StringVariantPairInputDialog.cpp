#include "StringVariantPairInputDialog.h"

const QVector<std::pair<StringVariantPairInputDialog::InputType, QString>> &StringVariantPairInputDialog::getInputTypeStringVector()
{
    static const QVector<std::pair<StringVariantPairInputDialog::InputType, QString>> inputTypeStringPairsVector = {
        {StringVariantPairInputDialog::InputType::IT_STRING, QString{tr("String")}},
        {StringVariantPairInputDialog::InputType::IT_NUMBER, QString{tr("Number")}},
        {StringVariantPairInputDialog::InputType::IT_URL,    QString{tr("URL")}}
    };
    
    return inputTypeStringPairsVector;
}

StringVariantPairInputDialog::StringVariantPairInputDialog(QString &key,
                                                           QVariant &value,
                                                           QWidget *parent)
    : QDialog{parent},
      m_key{key},
      m_value{value}
{
    QLabel *keyLabel   = new QLabel{tr("Key")};
    QLabel *typeLabel  = new QLabel{tr("Type")};
    QLabel *valueLabel = new QLabel{tr("Value")};
    
    QVBoxLayout *labelsLayout = new QVBoxLayout{};
    
    labelsLayout->addWidget(keyLabel);
    labelsLayout->addWidget(typeLabel);
    labelsLayout->addWidget(valueLabel);
    
    m_keyLineEdit       = new QLineEdit{};
    m_inputTypeComboBox = new QComboBox{};
    m_valueLineEdit     = new QLineEdit{};
    
    foreach (const auto &type, getInputTypeStringVector())
        m_inputTypeComboBox->addItem(type.second, type.first);
    
    m_inputTypeComboBox->setCurrentIndex(0);
    
    QVBoxLayout *inputsLayout = new QVBoxLayout{};
    
    inputsLayout->addWidget(m_keyLineEdit);
    inputsLayout->addWidget(m_inputTypeComboBox);
    inputsLayout->addWidget(m_valueLineEdit);
    
    QHBoxLayout *labelsInputsLayout = new QHBoxLayout{};
    
    labelsInputsLayout->addLayout(labelsLayout);
    labelsInputsLayout->addLayout(inputsLayout);
    
    m_acceptButton = new QPushButton{tr("Accept")};
    m_cancelButton = new QPushButton{tr("Cancel")};
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout{};
    
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_acceptButton);
    buttonsLayout->addWidget(m_cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    
    mainLayout->addLayout(labelsInputsLayout);
    mainLayout->addLayout(buttonsLayout);
    
    connect(m_acceptButton, &QPushButton::clicked, this, &StringVariantPairInputDialog::processAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
}

void StringVariantPairInputDialog::processAccept()
{
    if (m_keyLineEdit->text().isEmpty() || m_valueLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Provided data is not full!"));
        
        return;
    }
    
    QString key{m_keyLineEdit->text()};
    
    bool      isConvOK{false};
    InputType type    {static_cast<InputType>(m_inputTypeComboBox->currentData().toUInt(&isConvOK))};
    
    if (!isConvOK) {
        QMessageBox::warning(this, tr("Error"), tr("Provided type is incorrect!"));
        
        return;
    }
    
    QVariant value{};
    
    if (!stringToVariantOfInputType(type, m_valueLineEdit->text(), value)) {
        QMessageBox::warning(this, tr("Error"), tr("Provided value is incorrect!"));
        
        return;
    }
    
    m_key   = std::move(key);
    m_value = std::move(value);
    
    QDialog::accept();
}

bool StringVariantPairInputDialog::stringToVariantOfInputType(const InputType type,
                                                              const QString &string,
                                                              QVariant &variant)
{
    if (type == InputType::IT_INVALID)
        return false;
    
    QVariant variantBuffer{};
    
    switch (type) {
    case InputType::IT_NUMBER: {
        variantBuffer = stringToNumberVariant(string);
        
        break;
    }
    case InputType::IT_STRING: {
        variantBuffer = string;
        
        break;
    }
    case InputType::IT_URL: {
        variantBuffer = QUrl{string};
        
        break;
    }
    default: return false;
    }
    
    if (variantBuffer.isNull()) return false;
    
    variant = std::move(variantBuffer);
    
    return true;
}

QVariant StringVariantPairInputDialog::stringToNumberVariant(const QString &string)
{
    bool isConvOK{false};
    
    string.toDouble(&isConvOK);
    
    if (isConvOK) return QVariant{string.toDouble(&isConvOK)};
    
    string.toUInt(&isConvOK);
    
    if (isConvOK) return QVariant{string.toUInt(&isConvOK)};
    
    string.toInt(&isConvOK);
    
    if (isConvOK) return QVariant{string.toInt(&isConvOK)};
    
    string.toULongLong(&isConvOK);
    
    if (isConvOK) return QVariant{string.toULongLong(&isConvOK)};
    
    string.toLongLong(&isConvOK);
    
    if (isConvOK) return QVariant{string.toLongLong(&isConvOK)};
    
    return QVariant{};
}
