#include "DatabaseSettingsBase.h"

DatabaseSettingsBase::DatabaseSettingsBase()
    : m_dbType{DatabaseContext::DatabaseType::DT_INVALID},
      m_dbUrl{},
      m_additionalProps{}
{
    
}

DatabaseSettingsBase::DatabaseSettingsBase(DatabaseSettingsBase &&settings)
    : m_dbType{settings.m_dbType},
      m_dbUrl{std::move(settings.m_dbUrl)},
      m_additionalProps{std::move(settings.m_additionalProps)}
{
    
}

DatabaseSettingsBase::DatabaseSettingsBase(const QUrl &url,
                                           const DatabaseContext::DatabaseType dbType,
                                           AdditionalPropsMap &&additionalProps)
    : m_dbType{dbType},
      m_dbUrl{url},
      m_additionalProps{std::move(additionalProps)}
{
    
}

DatabaseContext::DatabaseType DatabaseSettingsBase::getDatabaseType() const
{
    return m_dbType;
}

const QUrl &DatabaseSettingsBase::getDatabaseUrl() const
{
    return m_dbUrl;
}

const DatabaseSettingsBase::AdditionalPropsMap &DatabaseSettingsBase::getAdditionalProps() const
{
    return m_additionalProps;
}

bool DatabaseSettingsBase::toJson (QJsonObject &json) const
{
    if (!isValid()) return false;
    
    QJsonObject jsonBuffer{};
    
    jsonBuffer[C_DATABASE_TYPE_PROP_NAME] = m_dbType;
    jsonBuffer[C_DATABASE_URL_PROP_NAME]  = m_dbUrl.toString(QUrl::ComponentFormattingOption::FullyEncoded);
    
    QJsonObject additionalPropsObj{};
    
    if (!m_additionalProps.empty()) {
        for (auto i = m_additionalProps.begin(); i != m_additionalProps.end(); ++i) {
            if (i.key().isEmpty()) return false;
            
            additionalPropsObj[i.key()] = i.value().toJsonValue();
        }
        
        if (additionalPropsObj.isEmpty()) return false;
    }
    
    jsonBuffer[C_DATABASE_ADDITIONAL_PROPS_PROP_NAME] = additionalPropsObj;
    
    if (jsonBuffer.isEmpty()) return false;
    
    json = std::move(jsonBuffer);
    
    return true;
}

bool DatabaseSettingsBase::fromJson(const QJsonObject &json)
{
    if (json.isEmpty()) return false;
    
    if (!json.contains(C_DATABASE_TYPE_PROP_NAME)
     || !json.contains(C_DATABASE_URL_PROP_NAME))
    {
        return false;
    }
    
    if (!json[C_DATABASE_TYPE_PROP_NAME].isDouble()
     || !json[C_DATABASE_URL_PROP_NAME].isString())
    {
        return false;
    }
    
    bool isNumbConvOK{false};
    
    DatabaseContext::DatabaseType dbTypeBuffer{static_cast<DatabaseContext::DatabaseType>(json[C_DATABASE_TYPE_PROP_NAME].toVariant().toUInt(&isNumbConvOK))};
    QString                       dbUrlBuffer {json[C_DATABASE_URL_PROP_NAME].toString()};
    
    if (!isNumbConvOK || dbUrlBuffer.isEmpty()) return false;
    
    m_dbType = dbTypeBuffer;
    m_dbUrl  = dbUrlBuffer;
    
    if (!json.contains(C_DATABASE_ADDITIONAL_PROPS_PROP_NAME))
        return true;
    
    if (!json[C_DATABASE_ADDITIONAL_PROPS_PROP_NAME].isObject())
        return false;
    
    QJsonObject additionalPropsObj{json[C_DATABASE_ADDITIONAL_PROPS_PROP_NAME].toObject()};
    AdditionalPropsMap additionalPropsBuffer{};
    
    for (auto i = additionalPropsObj.begin(); i != additionalPropsObj.end(); ++i) {
        if (i.key().isEmpty() || i.value().isUndefined()) return false;
        
         additionalPropsBuffer[i.key()] = i.value().toVariant();
    }
    
    m_additionalProps = std::move(additionalPropsBuffer);
    
    return isValid();
}

bool DatabaseSettingsBase::isValid() const
{
    return m_dbUrl.isValid() && m_dbType != DatabaseContext::DatabaseType::DT_INVALID;
}

bool DatabaseSettingsBase::isBaseSet() const
{
    return isValid();
}
