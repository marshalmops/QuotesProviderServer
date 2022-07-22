#include "DatabaseSettingsSQLite.h"

DatabaseSettingsSQLite::DatabaseSettingsSQLite(const QUrl &filename)
    : DatabaseSettingsBase{filename}
{
    
}

DatabaseContext::DatabaseType DatabaseSettingsSQLite::getDatabaseType() const
{
    return DatabaseContext::DatabaseType::DT_SQLITE;
}
