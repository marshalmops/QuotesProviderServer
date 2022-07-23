#ifndef DATABASESETTINGSSQLITE_H
#define DATABASESETTINGSSQLITE_H

#include "DatabaseSettingsBase.h"

class DatabaseSettingsSQLite : public DatabaseSettingsBase
{
public:
    DatabaseSettingsSQLite(DatabaseSettingsBase &&settingsBase);
    DatabaseSettingsSQLite(const QUrl &filename);
    
//    virtual bool toJson  (QJsonObject &json) const override;
//    virtual bool fromJson(const QJsonObject &json,
//                          bool loadBase = true) override;
    
    virtual bool isValid() const override;
};

#endif // DATABASESETTINGSSQLITE_H
