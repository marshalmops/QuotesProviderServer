#include "EntitySession.h"

EntitySession::EntitySession(const CoreContext::Id userId,
                             const CoreContext::Hash token,
                             const QDateTime &expirationDateTime,
                             const QDateTime &creationDateTime)
    : EntityBase{CoreContext::EntityType::ET_SESSION},
      m_userId{userId},
      m_token{token},
      m_creationDateTime{creationDateTime},
      m_expirationDateTime{expirationDateTime}
{
    
}

CoreContext::Id EntitySession::getUserId() const
{
    return m_userId;
}

CoreContext::Hash EntitySession::getToken() const
{
    return m_token;
}

const QDateTime &EntitySession::getCreationDateTime() const
{
    return m_creationDateTime;
}

const QDateTime &EntitySession::getExpirationDateTime() const
{
    return m_expirationDateTime;
}

bool EntitySession::isValid() const
{
    return (!m_token.isEmpty() && !m_expirationDateTime.isNull()
         && !m_creationDateTime.isNull()
         && (m_expirationDateTime > m_creationDateTime)
         && EntityBase::isValid());
}
