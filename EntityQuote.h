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
    constexpr static const char* C_AUTHOR_PROP_NAME             = "author";
    constexpr static const char* C_RATING_PROP_NAME             = "rating";
    constexpr static const char* C_CREATOR_ID_PROP_NAME         = "creator_id";
    constexpr static const char* C_CREATION_DATE_TIME_PROP_NAME = "creation_date_time";
    
    EntityQuote(const QString &text = QString{},
                const QString &author = QString{},
                const QDateTime &creationDateTime = QDateTime::currentDateTime(),
                const CoreContext::Id creatorId = 0,
                const CoreContext::Id id = 0,
                const Rating rating = 0);
    
    CoreContext::Id  getId              () const;
    const QString&   getText            () const;
    const QString&   getAuthor          () const;
    Rating           getRating          () const;
    CoreContext::Id  getCreatorId       () const;
    const QDateTime& getCreationDateTime() const;
    
    virtual bool isValid() const override;
    
private:
    CoreContext::Id m_id;
    QString         m_text;
    QString         m_author;
    Rating          m_rating;
    CoreContext::Id m_creatorId;
    QDateTime       m_creationDateTime;
    
};

#endif // ENTITYQUOTE_H
