#ifndef FILESPROCESSORSETTINGS_H
#define FILESPROCESSORSETTINGS_H

#include "FilesProcessorInterface.h"

#include "DatabaseLayerCreator.h"

#include "DatabaseSettingsContainerBase.h"

class FilesProcessorSettings : public virtual FilesProcessorInterface
{
public:
    FilesProcessorSettings();
    
    bool saveSettings();
    bool loadSettings();
};

#endif // FILESPROCESSORSETTINGS_H
