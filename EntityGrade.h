#ifndef ENTITYGRADE_H
#define ENTITYGRADE_H

#include "EntityBase.h"

class EntityGrade : public EntityBase
{
public:
    constexpr static const char* C_GRADE_TABLE_NAME = "Grades";
    
    constexpr static const char* C_QUOTE_ID_PROP_NAME    = "quote_id";
    constexpr static const char* C_DEVICE_HASH_PROP_NAME = "device_hash";
    constexpr static const char* C_GRADE_PROP_NAME       = "grade";
    
    EntityGrade(const CoreContext::Id quoteId = 0,
                const CoreContext::Hash deviceHash = QString{},
                const CoreContext::QuoteGrade grade = CoreContext::QuoteGrade::QG_INVALID);
    
    CoreContext::Id         getQuoteId   () const;
    CoreContext::Hash       getDeviceHash() const;
    CoreContext::QuoteGrade getGrade     () const;
    
    virtual bool isValid() const override;
    
private:
    CoreContext::Id         m_quoteId;
    CoreContext::Hash       m_deviceHash;
    CoreContext::QuoteGrade m_grade;
};

#endif // ENTITYGRADE_H
