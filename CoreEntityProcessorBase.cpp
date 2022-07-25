#include "CoreEntityProcessorBase.h"

bool CoreEntityProcessorBase::entityToJSON(const EntityBase *const entity,
                                           QJsonObject &jsonObject)
{
    if (!entity->isValid()) return false;
    
    switch (entity->getType()) {
    case CoreContext::EntityType::ET_GRADE:   return gradeToJSON(dynamic_cast<const EntityGrade*>(entity), jsonObject);
    case CoreContext::EntityType::ET_QUOTE:   return quoteToJSON(dynamic_cast<const EntityQuote*>(entity), jsonObject);
    case CoreContext::EntityType::ET_SESSION: return sessionToJSON(dynamic_cast<const EntitySession*>(entity), jsonObject);
    case CoreContext::EntityType::ET_USER:    return userToJSON(dynamic_cast<const EntityUser*>(entity), jsonObject);
    }
    
    return false;
}

bool CoreEntityProcessorBase::jsonToEntity(const CoreContext::EntityType entityType, 
                                           const QJsonObject &jsonObject,
                                           std::unique_ptr<EntityBase> &entity)
{
    if (jsonObject.isEmpty()) return false;
    
    switch (entityType) {
    case CoreContext::EntityType::ET_GRADE:   return jsonToGrade(jsonObject, entity);
    case CoreContext::EntityType::ET_QUOTE:   return jsonToQuote(jsonObject, entity);
    //case CoreContext::EntityType::ET_SESSION: return jsonToSession(jsonObject, entity);
    case CoreContext::EntityType::ET_USER:    return jsonToUser(jsonObject, entity);
    }
    
    return false;
}

bool CoreEntityProcessorBase::gradeToJSON(const EntityGrade * const grade, 
                                          QJsonObject &jsonObject)
{
    if (!grade) return false;
    
    QJsonObject jsonObjectBuffer{};
    
    jsonObjectBuffer[EntityGrade::C_QUOTE_ID_PROP_NAME]    = QJsonValue::fromVariant(QVariant{grade->getQuoteId()});
    jsonObjectBuffer[EntityGrade::C_DEVICE_HASH_PROP_NAME] = grade->getDeviceHash();
    jsonObjectBuffer[EntityGrade::C_GRADE_PROP_NAME]       = grade->getGrade();
    
    if (jsonObjectBuffer.isEmpty()) return false;
    
    jsonObject = std::move(jsonObjectBuffer);
    
    return true;
}

bool CoreEntityProcessorBase::quoteToJSON(const EntityQuote * const quote,
                                          QJsonObject &jsonObject)
{
    if (!quote) return false;
    
    QJsonObject jsonObjectBuffer{};
    
    jsonObjectBuffer[EntityQuote::C_ID_PROP_NAME]                 = QJsonValue::fromVariant(QVariant{quote->getId()});
    jsonObjectBuffer[EntityQuote::C_TEXT_PROP_NAME]               = quote->getText();
    jsonObjectBuffer[EntityQuote::C_AUTHOR_PROP_NAME]             = quote->getAuthor();
    jsonObjectBuffer[EntityQuote::C_RATING_PROP_NAME]             = quote->getRating();
    jsonObjectBuffer[EntityQuote::C_CREATOR_ID_PROP_NAME]         = QJsonValue::fromVariant(QVariant{quote->getCreatorId()});
    jsonObjectBuffer[EntityQuote::C_CREATION_DATE_TIME_PROP_NAME] = quote->getCreationDateTime().toString();
    
    if (jsonObjectBuffer.isEmpty()) return false;
    
    jsonObject = std::move(jsonObjectBuffer);
    
    return true;
}

bool CoreEntityProcessorBase::sessionToJSON(const EntitySession * const session, 
                                            QJsonObject &jsonObject)
{
    if (!session) return false;
    
    QJsonObject jsonObjectBuffer{};
    
    jsonObjectBuffer[EntitySession::C_ID_PROP_NAME]                   = QJsonValue::fromVariant(QVariant{session->getUserId()});
    jsonObjectBuffer[EntitySession::C_TOKEN_PROP_NAME]                = session->getToken();
    jsonObjectBuffer[EntitySession::C_CREATION_DATE_TIME_PROP_NAME]   = session->getCreationDateTime().toString();
    jsonObjectBuffer[EntitySession::C_EXPIRATION_DATE_TIME_PROP_NAME] = session->getExpirationDateTime().toString();
    
    if (jsonObjectBuffer.isEmpty()) return false;
    
    jsonObject = std::move(jsonObjectBuffer);
    
    return true;
}

bool CoreEntityProcessorBase::userToJSON(const EntityUser * const user, 
                                         QJsonObject &jsonObject)
{
    if (!user) return false;
    
    QJsonObject jsonObjectBuffer{};
    
    jsonObjectBuffer[EntityUser::C_ID_PROP_NAME]       = QJsonValue::fromVariant(QVariant{user->getId()});
    jsonObjectBuffer[EntityUser::C_EMAIL_PROP_NAME]    = user->getEmail();
    jsonObjectBuffer[EntityUser::C_PASSWORD_PROP_NAME] = user->getPasswordHash();
    
    if (jsonObjectBuffer.isEmpty()) return false;
    
    jsonObject = std::move(jsonObjectBuffer);
    
    return true;
}

bool CoreEntityProcessorBase::jsonToGrade(const QJsonObject &jsonObject, 
                                          std::unique_ptr<EntityBase> &grade)
{
    if (!jsonObject.contains(EntityGrade::C_QUOTE_ID_PROP_NAME)
     || !jsonObject.contains(EntityGrade::C_DEVICE_HASH_PROP_NAME)
     || !jsonObject.contains(EntityGrade::C_GRADE_PROP_NAME))
    {
        return false;
    }
    
    if (!jsonObject[EntityGrade::C_QUOTE_ID_PROP_NAME].isDouble()
     || !jsonObject[EntityGrade::C_DEVICE_HASH_PROP_NAME].isString()
     || !jsonObject[EntityGrade::C_GRADE_PROP_NAME].isDouble())
    {
        return false;
    }
    
    bool isConvOK{false};
    
    CoreContext::Id quoteId{jsonObject[EntityGrade::C_QUOTE_ID_PROP_NAME].toVariant().toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    QString deviceHash{jsonObject[EntityGrade::C_DEVICE_HASH_PROP_NAME].toString()};
    
    if (deviceHash.isEmpty()) return false;
    
    CoreContext::QuoteGrade gradeId{static_cast<CoreContext::QuoteGrade>(jsonObject[EntityGrade::C_GRADE_PROP_NAME].toInt(CoreContext::QuoteGrade::QG_INVALID))};
    
    if (gradeId == CoreContext::QuoteGrade::QG_INVALID)
        return false;
    
    std::unique_ptr<EntityGrade> gradeBuffer{std::make_unique<EntityGrade>(quoteId, deviceHash, gradeId)};
    
    if (!gradeBuffer->isValid()) return false;
    
    grade = std::move(gradeBuffer);
    
    return true;
}

bool CoreEntityProcessorBase::jsonToQuote(const QJsonObject &jsonObject, 
                                          std::unique_ptr<EntityBase> &quote)
{
    if (!jsonObject.contains(EntityQuote::C_TEXT_PROP_NAME)
     || !jsonObject.contains(EntityQuote::C_AUTHOR_PROP_NAME))
    {
        return false;
    }
    
    if (!jsonObject[EntityQuote::C_TEXT_PROP_NAME].isString()
     || !jsonObject[EntityQuote::C_AUTHOR_PROP_NAME].isString())
    {
        return false;
    }
    
    QString text  {jsonObject[EntityQuote::C_TEXT_PROP_NAME].toString()};
    QString author{jsonObject[EntityQuote::C_AUTHOR_PROP_NAME].toString()};
    
    if (text.isEmpty() || author.isEmpty())
        return false;
    
    std::unique_ptr<EntityQuote> quoteBuffer{std::make_unique<EntityQuote>(text, author)};
    
    if (!quoteBuffer->isValid()) return false;
    
    quote = std::move(quoteBuffer);
    
    return true;
}

//bool CoreEntityProcessorBase::jsonToSession(const QJsonObject &jsonObject,
//                                            std::unique_ptr<EntityBase> &session)
//{
//    // only token...
    
//    if (!jsonObject.contains(EntitySession::C_TOKEN_PROP_NAME))
//    {
//        return false;
//    }
    
//    if (!jsonObject[EntitySession::C_TOKEN_PROP_NAME].isString())
//    {
//        return false;
//    }
    
//    CoreContext::Hash token{jsonObject[EntitySession::C_TOKEN_PROP_NAME].toString()};
    
//    if (token.isEmpty()) return false;
    
//    std::unique_ptr<EntityQuote> quoteBuffer{std::make_unique<EntityQuote>(text)};
    
//    if (!quoteBuffer->isValid()) return false;
    
//    quote = std::move(quoteBuffer);
    
//    return true;
//}

bool CoreEntityProcessorBase::jsonToUser(const QJsonObject &jsonObject, 
                                         std::unique_ptr<EntityBase> &user)
{
    if (!jsonObject.contains(EntityUser::C_EMAIL_PROP_NAME)
     || !jsonObject.contains(EntityUser::C_PASSWORD_PROP_NAME))
    {
        return false;
    }
    
    if (!jsonObject[EntityUser::C_EMAIL_PROP_NAME].isString()
     || !jsonObject[EntityUser::C_PASSWORD_PROP_NAME].isString())
    {
        return false;
    }
    
    QString email   {jsonObject[EntityUser::C_EMAIL_PROP_NAME].toString()};
    QString password{jsonObject[EntityUser::C_PASSWORD_PROP_NAME].toString()};
    
    if (email.isEmpty() || password.isEmpty())
        return false;
    
    std::unique_ptr<EntityUser> userBuffer{std::make_unique<EntityUser>(email, password)};
    
    if (!userBuffer->isValid()) return false;
    
    user = std::move(userBuffer);
    
    return true;
}
