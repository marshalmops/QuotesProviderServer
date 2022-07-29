#ifndef DATABASESETTINGSSQLITE_H
#define DATABASESETTINGSSQLITE_H

#include "DatabaseSettingsBase.h"

class DatabaseSettingsSQLite : public DatabaseSettingsBase
{
public:
    constexpr static const char* C_DEFAULT_FILENAME = "database.db";
    
    DatabaseSettingsSQLite(DatabaseSettingsBase &&settingsBase);
    DatabaseSettingsSQLite(const QUrl &filename = QString{C_DEFAULT_FILENAME});
    
//    virtual bool toJson  (QJsonObject &json) const override;
//    virtual bool fromJson(const QJsonObject &json,
//                          bool loadBase = true) override;
    
    virtual bool isValid() const override;
};

#endif // DATABASESETTINGSSQLITE_H
