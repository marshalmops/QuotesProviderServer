#ifndef ENTITYUSER_H
#define ENTITYUSER_H

#include "EntityBase.h"

class EntityUser : public EntityBase
{
public:
    constexpr static const char* C_USER_TABLE_NAME = "Users";
    
    constexpr static const char* C_ID_PROP_NAME       = "id";
    constexpr static const char* C_EMAIL_PROP_NAME    = "email";
    constexpr static const char* C_PASSWORD_PROP_NAME = "password";
    
    EntityUser(const QString &email = QString{},
               const CoreContext::Hash &passwordHash = CoreContext::Hash{},
               const CoreContext::Id id = 0);
    
    CoreContext::Id           getId          () const;
    const QString&            getEmail       () const;
    const CoreContext::Hash&  getPasswordHash() const;
    
    virtual bool isValid() const override;
    
private:
    CoreContext::Id   m_id;
    QString           m_email;
    CoreContext::Hash m_passwordHash;
};

#endif // ENTITYUSER_H
