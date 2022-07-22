#ifndef DATABASESETTINGSCONTAINEREDITABLE_H
#define DATABASESETTINGSCONTAINEREDITABLE_H

#include "DatabaseSettingsContainerBase.h"

class DatabaseSettingsContainerEditable : public DatabaseSettingsContainerBase
{
public:
    DatabaseSettingsContainerEditable() = delete;
    
    static bool setSettings(std::unique_ptr<DatabaseSettingsBase> &&settings);
};

#endif // DATABASESETTINGSCONTAINEREDITABLE_H
