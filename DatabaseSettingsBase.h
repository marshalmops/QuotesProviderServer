#ifndef DATABASESETTINGSBASE_H
#define DATABASESETTINGSBASE_H

#include <QString>
#include <QUrl>
#include <QVariant>
#include <memory>

#include "DatabaseContext.h"

class DatabaseSettingsBase
{
public:
    constexpr static const char* C_DEFAULT_DATABASE_SETTINGS_FILENAME = "dbSettings.json";
    
    constexpr static const char* C_DATABASE_TYPE_PROP_NAME             = "dbType";
    constexpr static const char* C_DATABASE_HOST_PROP_NAME             = "dbUrl";
    constexpr static const char* C_DATABASE_ADDITIONAL_PROPS_PROP_NAME = "additionalProps";
    
    using AdditionalPropsMap = QMap<QString, QVariant>;
    
public:
    DatabaseSettingsBase(const QUrl &url,
                         const AdditionalPropsMap &additionalProps = AdditionalPropsMap{});
    
    virtual DatabaseContext::DatabaseType getDatabaseType() const = 0;
    
    const QUrl&                   getDatabaseUrl    () const;
    const AdditionalPropsMap&     getAdditionalProps() const;
    
protected:
    QUrl                          m_dbUrl;
    AdditionalPropsMap            m_additionalProps;
};

#endif // DATABASESETTINGSBASE_H
