#ifndef SETTINGSINTERFACE_H
#define SETTINGSINTERFACE_H

#include <QJsonObject>
#include <QJsonValue>

class SettingsInterface
{
public:
    SettingsInterface()                          = default;
    SettingsInterface(SettingsInterface &&other) = default;
            
    virtual ~SettingsInterface() = default; 
    
    virtual bool toJson  (QJsonObject &json) const = 0;
    virtual bool fromJson(const QJsonObject &json) = 0;
    
    virtual bool isValid() const = 0;
};

#endif // SETTINGSINTERFACE_H
