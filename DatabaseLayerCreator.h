#ifndef DATABASELAYERCREATOR_H
#define DATABASELAYERCREATOR_H

#include "DatabaseSettingsContainerEditable.h"

#include "DatabaseSettingsSQLite.h"

class DatabaseLayerCreator
{
public:
    DatabaseLayerCreator() = delete;
    
    static bool createDatabaseSettingsUsingBase(std::unique_ptr<DatabaseSettingsBase> &&databaseSettingsBase);
    static bool createDatabaseFacade           (..);
};

#endif // DATABASELAYERCREATOR_H
