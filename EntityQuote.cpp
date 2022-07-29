#include "EntityQuote.h"

EntityQuote::EntityQuote(const QString &text, 
                         const QString &author,
                         const CoreContext::Hash &textHash,
                         const QDateTime &creationDateTime,
                         const CoreContext::Id creatorId,
                         const CoreContext::Id id,
                         const Rating rating)
    : EntityBase{CoreContext::EntityType::ET_QUOTE},
      m_id{id},
      m_text{text},
      m_textHash{textHash},
      m_author{author},
      m_rating{rating},
      m_creatorId{creatorId},
      m_creationDateTime{creationDateTime}
{
    
}

EntityQuote::EntityQuote(const EntityQuote &quote)
    : EntityBase{quote.m_type}
{
    m_id               = quote.m_id;
    m_text             = quote.m_text;
    m_textHash         = quote.m_textHash;
    m_author           = quote.m_author;
    m_rating           = quote.m_rating;
    m_creatorId        = quote.m_creatorId;
    m_creationDateTime = quote.m_creationDateTime;
}

EntityQuote &EntityQuote::operator=(EntityQuote &&quote)
{
    m_type             = quote.m_type;
    m_id               = quote.m_id;
    m_text             = std::move(quote.m_text);
    m_textHash         = std::move(quote.m_textHash);
    m_author           = std::move(quote.m_author);
    m_rating           = quote.m_rating;
    m_creatorId        = quote.m_creatorId;
    m_creationDateTime = std::move(quote.m_creationDateTime);
}

CoreContext::Id EntityQuote::getId() const
{
    return m_id;
}

const QString &EntityQuote::getText() const
{
    return m_text;
}

const CoreContext::Hash &EntityQuote::getTextHash() const
{
    return m_textHash;
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
