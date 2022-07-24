#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include "CoreContext.h"

class EntityBase
{
public:
    EntityBase(const CoreContext::EntityType type);
    virtual ~EntityBase() = default;
    
    CoreContext::EntityType getType() const;
    
    virtual bool isValid() const;
    
protected:
    CoreContext::EntityType m_type;
};

#endif // ENTITYBASE_H
