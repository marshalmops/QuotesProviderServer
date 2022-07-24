#include "EntityUser.h"

EntityUser::EntityUser(const QString &email,
                       const CoreContext::Hash &passwordHash, 
                       const CoreContext::Id id)
    : EntityBase{CoreContext::EntityType::ET_USER},
      m_id{id},
      m_email{email},
      m_passwordHash{passwordHash}
{
    
}

CoreContext::Id EntityUser::getId() const
{
    return m_id;
}

const QString &EntityUser::getEmail() const
{
    return m_email;
}

const CoreContext::Hash &EntityUser::getPasswordHash() const
{
    return m_passwordHash;
}

bool EntityUser::isValid() const
{
    return (!m_email.isEmpty() && !m_passwordHash.isEmpty()
          && EntityBase::isValid());
}
