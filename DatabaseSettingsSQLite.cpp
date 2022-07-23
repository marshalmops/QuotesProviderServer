#include "DatabaseSettingsSQLite.h"

DatabaseSettingsSQLite::DatabaseSettingsSQLite(DatabaseSettingsBase &&settingsBase)
    : DatabaseSettingsBase(std::move(settingsBase))
{
    
}

DatabaseSettingsSQLite::DatabaseSettingsSQLite(const QUrl &filename)
    : DatabaseSettingsBase{filename, DatabaseContext::DatabaseType::DT_SQLITE}
{
    
}

//bool DatabaseSettingsSQLite::toJson(QJsonObject &json) const
//{
//    return DatabaseSettingsBase::toJson(json);
//}

//bool DatabaseSettingsSQLite::fromJson(const QJsonObject &json, 
//                                      bool loadBase)
//{
//    return DatabaseSettingsBase::fromJson(json, loadBase);
//}

bool DatabaseSettingsSQLite::isValid() const
{
    return DatabaseSettingsBase::isValid();
}
