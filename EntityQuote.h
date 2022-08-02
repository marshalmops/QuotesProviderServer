#ifndef ENTITYQUOTE_H
#define ENTITYQUOTE_H

#include <QDateTime>

#include "EntityBase.h"

class EntityQuote : public EntityBase
{
public:
    using Rating = int64_t;
    
    constexpr static const char* C_QUOTE_TABLE_NAME = "Quotes";
    
    constexpr static const char* C_ID_PROP_NAME                 = "id";
    constexpr static const char* C_TEXT_PROP_NAME               = "text";
    constexpr static const char* C_TEXT_HASH_PROP_NAME          = "text_hash";
    constexpr static const char* C_AUTHOR_PROP_NAME             = "author";
    constexpr static const char* C_CREATOR_ID_PROP_NAME         = "creator_id";
    constexpr static const char* C_CREATION_DATE_TIME_PROP_NAME = "creation_date_time";
    constexpr static const char* C_RATING                       = "rating";
    
    EntityQuote(const QString &text = QString{},
                const QString &author = QString{},
                const CoreContext::Hash &textHash = CoreContext::Hash{},
                const QDateTime &creationDateTime = QDateTime::currentDateTime(),
                const CoreContext::Id creatorId = 0,
                const CoreContext::Id id = 0,
                const Rating rating = 0);
    EntityQuote(const EntityQuote &quote);
    EntityQuote& operator=(EntityQuote &&quote);
    
    CoreContext::Id          getId              () const;
    const QString&           getText            () const;
    const CoreContext::Hash& getTextHash        () const;
    const QString&           getAuthor          () const;
    CoreContext::Id          getCreatorId       () const;
    const QDateTime&         getCreationDateTime() const;
    Rating                   getRating          () const;
    
    virtual bool isValid() const override;
    
private:
    CoreContext::Id   m_id;
    QString           m_text;
    CoreContext::Hash m_textHash;
    QString           m_author;
    CoreContext::Id   m_creatorId;
    QDateTime         m_creationDateTime;
    Rating            m_rating;
};

#endif // ENTITYQUOTE_H
