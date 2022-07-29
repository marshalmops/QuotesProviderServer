#ifndef CORESETTINGSBASE_H
#define CORESETTINGSBASE_H

#include <QCryptographicHash>

#include "SettingsInterface.h"

class CoreSettingsBase : public SettingsInterface
{
public:
    constexpr static const char* C_DEFAULT_CORE_SETTINGS_FILENAME = "coreSettings.json";
    
    constexpr static const char* C_CORE_HASHING_SALT_PROP_NAME          = "hashing_salt";
    constexpr static const char* C_CORE_HASHING_ALGO_PROP_NAME          = "hashing_algo";
    constexpr static const char* C_CORE_TOKEN_EXPIRATION_TIME_PROP_NAME = "token_expiration_time";
    
    constexpr static const char*                         C_DEFAULT_HASHING_SALT          = "someSalt";
    constexpr static const QCryptographicHash::Algorithm C_DEFAULT_HASHING_ALGO          = QCryptographicHash::Algorithm::Sha256;
    constexpr static const uint32_t                      C_DEFAULT_TOKEN_EXPIRATION_TIME = 86400;
    
public:
    CoreSettingsBase(CoreSettingsBase &&other);
    CoreSettingsBase(const QString& hashingSalt = C_DEFAULT_HASHING_SALT,
                     const QCryptographicHash::Algorithm hashingAlgo = C_DEFAULT_HASHING_ALGO,
                     const uint32_t tokenExpirationTime = C_DEFAULT_TOKEN_EXPIRATION_TIME);
    
    const QString&                getHashingSalt        () const;
    QCryptographicHash::Algorithm getHashingAlgo        () const;
    uint32_t                      getTokenExpirationTime() const;
    
    virtual bool toJson  (QJsonObject &json) const override;
    virtual bool fromJson(const QJsonObject &json) override;
    
    virtual bool isValid() const override;
    
protected:
    QString                       m_hashingSalt;
    QCryptographicHash::Algorithm m_hashingAlgo;
    uint32_t                      m_tokenExpirationTime;
};

#endif // CORESETTINGSBASE_H
