#ifndef FILESPROCESSORSETTINGS_H
#define FILESPROCESSORSETTINGS_H

#include "FilesProcessorInterface.h"

#include "DatabaseSettingsBase.h"

class FilesProcessorSettings : public virtual FilesProcessorInterface
{
public:
    FilesProcessorSettings();
    
    bool saveSettings();
    bool loadSettings();
};

#endif // FILESPROCESSORSETTINGS_H
