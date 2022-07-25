#ifndef FILESPROCESSORSETTINGS_H
#define FILESPROCESSORSETTINGS_H

#include "FilesProcessorInterface.h"

#include "DatabaseLayerCreator.h"

#include "SettingsContainerBase.h"

class FilesProcessorSettings : public virtual FilesProcessorInterface
{
public:
    FilesProcessorSettings();
    
    bool saveSettings();
    bool loadSettings();
    
protected:
    bool saveSettingsWithFileName(const QString &filename,
                                  const std::shared_ptr<SettingsInterface> &settingsToSave);
    bool loadSettingsContentWithFileName(const QString &filename,
                                         QJsonObject &settingsJson);
};

#endif // FILESPROCESSORSETTINGS_H
