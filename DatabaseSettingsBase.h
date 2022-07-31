#ifndef DATABASESETTINGSBASE_H
#define DATABASESETTINGSBASE_H

#include <QString>
#include <QUrl>
#include <QVariant>
#include <memory>
#include <QJsonObject>
#include <QMetaType>

#include "DatabaseContext.h"

#include "SettingsInterface.h"

class DatabaseSettingsBase : public SettingsInterface
{
public:
    constexpr static const char* C_DEFAULT_DATABASE_SETTINGS_FILENAME = "dbSettings.json";
    
    constexpr static const char* C_DATABASE_TYPE_PROP_NAME             = "dbType";
    constexpr static const char* C_DATABASE_URL_PROP_NAME              = "dbUrl";
    constexpr static const char* C_DATABASE_ADDITIONAL_PROPS_PROP_NAME = "additionalProps";
    
    using AdditionalPropsMap = QMap<QString, QVariant>;
    
public:
    DatabaseSettingsBase();
    DatabaseSettingsBase(DatabaseSettingsBase &&settings);
    DatabaseSettingsBase(const QUrl &url,
                         const DatabaseContext::DatabaseType dbType = DatabaseContext::DatabaseType::DT_INVALID,
                         AdditionalPropsMap &&additionalProps = AdditionalPropsMap{});
    
    DatabaseContext::DatabaseType getDatabaseType() const;
    
    const QUrl&               getDatabaseUrl    () const;
    const AdditionalPropsMap& getAdditionalProps() const;
    
    virtual bool toJson  (QJsonObject &json) const override;
    virtual bool fromJson(const QJsonObject &json) override;
    
    virtual bool isValid() const override;
    
protected:
    bool isBaseSet() const;
    
protected:
    DatabaseContext::DatabaseType m_dbType;
    QUrl                          m_dbUrl;
    AdditionalPropsMap            m_additionalProps;
};

#endif // DATABASESETTINGSBASE_H
