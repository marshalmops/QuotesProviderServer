#ifndef SETTINGSCONTAINEREDITABLE_H
#define SETTINGSCONTAINEREDITABLE_H

#include "SettingsContainerBase.h"

class SettingsContainerEditable : public SettingsContainerBase
{
public:
    SettingsContainerEditable() = delete;
    
    static bool setDatabaseSettings(std::unique_ptr<DatabaseSettingsBase> &&dbSettings);
    static bool setCoreSettings    (std::unique_ptr<CoreSettingsBase> &&coreSettings);
};

#endif // SETTINGSCONTAINEREDITABLE_H
