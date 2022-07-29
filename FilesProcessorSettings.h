#ifndef FILESPROCESSORSETTINGS_H
#define FILESPROCESSORSETTINGS_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "DatabaseLayerCreator.h"

#include "SettingsContainerBase.h"

class FilesProcessorSettings
{
public:
    FilesProcessorSettings() = delete;
    
    static bool saveSettings();
    static bool loadSettings();
    
protected:
    static bool saveSettingsWithFileName(const QString &filename,
                                  const std::shared_ptr<SettingsInterface> &settingsToSave);
    static bool loadSettingsContentWithFileName(const QString &filename,
                                         QJsonObject &settingsJson);
};

#endif // FILESPROCESSORSETTINGS_H
