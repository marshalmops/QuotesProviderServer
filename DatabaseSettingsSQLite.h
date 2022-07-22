#ifndef DATABASESETTINGSSQLITE_H
#define DATABASESETTINGSSQLITE_H

#include "DatabaseSettingsBase.h"

class DatabaseSettingsSQLite : public DatabaseSettingsBase
{
public:
    DatabaseSettingsSQLite(const QUrl &filename);
    
    virtual DatabaseContext::DatabaseType getDatabaseType() const override;
};

#endif // DATABASESETTINGSSQLITE_H
