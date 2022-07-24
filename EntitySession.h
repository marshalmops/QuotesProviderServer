#ifndef ENTITYSESSION_H
#define ENTITYSESSION_H

#include <QDateTime>

#include "EntityBase.h"

class EntitySession : public EntityBase
{
public:
    constexpr static const char* C_SESSION_TABLE_NAME = "Sessions";
    
    constexpr static const char* C_ID_PROP_NAME                   = "user_id";
    constexpr static const char* C_TOKEN_PROP_NAME                = "token";
    constexpr static const char* C_CREATION_DATE_TIME_PROP_NAME   = "creation_date_time";
    constexpr static const char* C_EXPIRATION_DATE_TIME_PROP_NAME = "expiration_date_time";
    
    EntitySession(const CoreContext::Id userId = 0,
                  const CoreContext::Hash token = CoreContext::Hash{},
                  const QDateTime &expirationDateTime = QDateTime{},
                  const QDateTime &creationDateTime = QDateTime::currentDateTime());
    
    CoreContext::Id   getUserId            () const;
    CoreContext::Hash getToken             () const;
    const QDateTime&  getCreationDateTime  () const;
    const QDateTime&  getExpirationDateTime() const;
    
    virtual bool isValid() const override;
    
private:
    CoreContext::Id   m_userId;
    CoreContext::Hash m_token;
    QDateTime         m_creationDateTime;
    QDateTime         m_expirationDateTime;
};

#endif // ENTITYSESSION_H
