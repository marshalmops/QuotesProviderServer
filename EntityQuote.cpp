#include "EntityQuote.h"

EntityQuote::EntityQuote(const QString &text, 
                         const QString &author,
                         const QDateTime &creationDateTime,
                         const CoreContext::Id creatorId,
                         const CoreContext::Id id,
                         const Rating rating)
    : EntityBase{CoreContext::EntityType::ET_QUOTE},
      m_id{id},
      m_text{text},
      m_author{author},
      m_rating{rating},
      m_creatorId{creatorId},
      m_creationDateTime{creationDateTime}
{
    
}

CoreContext::Id EntityQuote::getId() const
{
    return m_id;
}

const QString &EntityQuote::getText() const
{
    return m_text;
}

const QString &EntityQuote::getAuthor() const
{
    return m_author;
}

EntityQuote::Rating EntityQuote::getRating() const
{
    return m_rating;
}

CoreContext::Id EntityQuote::getCreatorId() const
{
    return m_creatorId;
}

const QDateTime &EntityQuote::getCreationDateTime() const
{
    return m_creationDateTime;
}

bool EntityQuote::isValid() const
{
    return (!m_text.isEmpty() && !m_author.isEmpty()
          && !m_creationDateTime.isNull()
          && EntityBase::isValid());
}
