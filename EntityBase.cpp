#include "EntityBase.h"


EntityBase::EntityBase(const CoreContext::EntityType type)
    : m_type{type}
{
    
}

CoreContext::EntityType EntityBase::getType() const
{
    return m_type;
}

bool EntityBase::isValid() const
{
    return m_type != CoreContext::EntityType::ET_INVALID;
}
