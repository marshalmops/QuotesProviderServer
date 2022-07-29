#include "CoreSettingsBase.h"

CoreSettingsBase::CoreSettingsBase(CoreSettingsBase &&other)
    : m_hashingSalt{std::move(other.m_hashingSalt)},
      m_hashingAlgo{other.m_hashingAlgo},
      m_tokenExpirationTime{other.m_tokenExpirationTime}
{
    
}

CoreSettingsBase::CoreSettingsBase(const QString &hashingSalt, 
                                   const QCryptographicHash::Algorithm hashingAlgo,
                                   const uint32_t tokenExpirationTime)
    : m_hashingSalt{hashingSalt},
      m_hashingAlgo{hashingAlgo},
      m_tokenExpirationTime{tokenExpirationTime}
{
    
}

const QString &CoreSettingsBase::getHashingSalt() const
{
    return m_hashingSalt;
}

QCryptographicHash::Algorithm CoreSettingsBase::getHashingAlgo() const
{
    return m_hashingAlgo;
}

uint32_t CoreSettingsBase::getTokenExpirationTime() const
{
    return m_tokenExpirationTime;
}

bool CoreSettingsBase::toJson(QJsonObject &json) const
{
    QJsonObject jsonBuffer{};
    
    jsonBuffer[C_CORE_HASHING_SALT_PROP_NAME]          = m_hashingSalt;
    jsonBuffer[C_CORE_HASHING_ALGO_PROP_NAME]          = m_hashingAlgo;
    jsonBuffer[C_CORE_TOKEN_EXPIRATION_TIME_PROP_NAME] = QJsonValue::fromVariant(QVariant{m_tokenExpirationTime});
    
    if (jsonBuffer.isEmpty()) return false;
    
    jsonBuffer = std::move(json);
    
    return true;
}

bool CoreSettingsBase::fromJson(const QJsonObject &json)
{
    if (json.isEmpty()) return false;
    
    if (!json.contains(C_CORE_HASHING_SALT_PROP_NAME)
     || !json.contains(C_CORE_HASHING_ALGO_PROP_NAME)
     || !json.contains(C_CORE_TOKEN_EXPIRATION_TIME_PROP_NAME))
    {
        return false;
    }
    
    if (!json[C_CORE_HASHING_SALT_PROP_NAME].isString()
     || !json[C_CORE_HASHING_ALGO_PROP_NAME].isDouble()
     || !json[C_CORE_TOKEN_EXPIRATION_TIME_PROP_NAME].isDouble())
    {
        return false;
    }
    
    QString hashingSalt{json[C_CORE_HASHING_SALT_PROP_NAME].toString()};
    
    if (hashingSalt.isEmpty()) return false;
    
    auto hashingAlgoRaw{json[C_CORE_HASHING_ALGO_PROP_NAME].toInt(-1)};
    
    if (hashingAlgoRaw < 0) return false;
    
    QCryptographicHash::Algorithm hashingAlgo{static_cast<QCryptographicHash::Algorithm>(hashingAlgoRaw)};
    
    bool isConvOK{false};
    
    uint32_t tokenExpirationTime{json[C_CORE_TOKEN_EXPIRATION_TIME_PROP_NAME].toVariant().toUInt(&isConvOK)};
    
    if (!isConvOK) return false;
    
    m_hashingSalt         = hashingSalt;
    m_hashingAlgo         = hashingAlgo;
    m_tokenExpirationTime = tokenExpirationTime;
    
    return isValid();
}

bool CoreSettingsBase::isValid() const
{
    return !m_hashingSalt.isEmpty() && m_tokenExpirationTime > 0;
}
