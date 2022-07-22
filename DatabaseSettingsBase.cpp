#include "DatabaseSettingsBase.h"

DatabaseSettingsBase::DatabaseSettingsBase(const QUrl &url, 
                                           const AdditionalPropsMap &additionalProps)
    : m_dbUrl{url},
      m_additionalProps{additionalProps}
{
    
}

const QUrl &DatabaseSettingsBase::getDatabaseUrl() const
{
    return m_dbUrl;
}

const DatabaseSettingsBase::AdditionalPropsMap &DatabaseSettingsBase::getAdditionalProps() const
{
    return m_additionalProps;
}
