#include "EntityGrade.h"


EntityGrade::EntityGrade(const CoreContext::Id quoteId,
                         const CoreContext::Hash deviceHash,
                         const CoreContext::QuoteGrade grade)
    : EntityBase{CoreContext::EntityType::ET_GRADE},
      m_quoteId{quoteId},
      m_deviceHash{deviceHash},
      m_grade{grade}
{
    
}

CoreContext::Id EntityGrade::getQuoteId() const
{
    return m_quoteId;
}

CoreContext::Hash EntityGrade::getDeviceHash() const
{
    return m_deviceHash;
}

CoreContext::QuoteGrade EntityGrade::getGrade() const
{
    return m_grade;
}

bool EntityGrade::isValid() const
{
    return (!m_deviceHash.isEmpty()
          && m_grade != CoreContext::QuoteGrade::QG_INVALID
          && EntityBase::isValid());
}
