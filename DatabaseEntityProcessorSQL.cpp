#include "DatabaseEntityProcessorSQL.h"

namespace {

bool getQtSqlQueryByDatabaseQueryResultPtr(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                           QSqlQuery &sqlQuery)
{
    DatabaseQueryResultStandard *queryResultSQL = dynamic_cast<DatabaseQueryResultStandard*>(queryResult.get());
    
    if (!queryResultSQL) return false;
    
    sqlQuery = queryResultSQL->getSqlResult();
    
    return true;
}

}

bool DatabaseEntityProcessorSQL::getEntityGradeByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                                     std::vector<std::shared_ptr<EntityBase>> &entities)
{
    QSqlQuery sqlQuery{};
    
    if (!getQtSqlQueryByDatabaseQueryResultPtr(queryResult, sqlQuery))
        return false;
    
    auto quoteIdRawValue    = sqlQuery.value(EntityGrade::C_QUOTE_ID_PROP_NAME);
    auto deviceHashRawValue = sqlQuery.value(EntityGrade::C_DEVICE_HASH_PROP_NAME);
    auto gradeRawValue      = sqlQuery.value(EntityGrade::C_GRADE_PROP_NAME);
    
    if (quoteIdRawValue.isNull() || deviceHashRawValue.isNull() || gradeRawValue.isNull())
        return false;
    
    bool isConvOK{false};
    
    CoreContext::Id quoteId{quoteIdRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    CoreContext::Hash deviceHash{deviceHashRawValue.toString()};
    CoreContext::QuoteGrade grade{static_cast<CoreContext::QuoteGrade>(gradeRawValue.toUInt(&isConvOK))};
    
    if (!isConvOK || deviceHash.isEmpty()) return false;
    
    auto newGrade = std::make_shared<EntityGrade>(quoteId, deviceHash, grade);
    
    if (!newGrade->isValid()) return false;
    
    entities.push_back(newGrade);
    
    return true;
}

bool DatabaseEntityProcessorSQL::getEntityUserByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                                    std::vector<std::shared_ptr<EntityBase>> &entities)
{
    QSqlQuery sqlQuery{};
    
    if (!getQtSqlQueryByDatabaseQueryResultPtr(queryResult, sqlQuery))
        return false;
    
    auto idRawValue       = sqlQuery.value(EntityUser::C_ID_PROP_NAME);
    auto emailRawValue    = sqlQuery.value(EntityUser::C_EMAIL_PROP_NAME);
    auto passwordRawValue = sqlQuery.value(EntityUser::C_PASSWORD_PROP_NAME);
    
    if (idRawValue.isNull() || emailRawValue.isNull() || passwordRawValue.isNull())
        return false;
    
    bool isConvOK{false};
    
    CoreContext::Id id{idRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    QString email   {emailRawValue.toString()};
    QString password{passwordRawValue.toString()};
    
    if (email.isEmpty() || password.isEmpty()) return false;
    
    auto newUser = std::make_shared<EntityUser>(email, password, id);
    
    if (!newUser->isValid()) return false;
    
    entities.push_back(newUser);
    
    return true;
}

bool DatabaseEntityProcessorSQL::getEntitySessionByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                                       std::vector<std::shared_ptr<EntityBase>> &entities)
{
    QSqlQuery sqlQuery{};
    
    if (!getQtSqlQueryByDatabaseQueryResultPtr(queryResult, sqlQuery))
        return false;
    
    auto userIdRawValue             = sqlQuery.value(EntitySession::C_ID_PROP_NAME);
    auto tokenRawValue              = sqlQuery.value(EntitySession::C_TOKEN_PROP_NAME);
    auto creationDateTimeRawValue   = sqlQuery.value(EntitySession::C_CREATION_DATE_TIME_PROP_NAME);
    auto expirationDateTimeRawValue = sqlQuery.value(EntitySession::C_EXPIRATION_DATE_TIME_PROP_NAME);
    
    if (userIdRawValue.isNull() || tokenRawValue.isNull() || creationDateTimeRawValue.isNull()
     || expirationDateTimeRawValue.isNull()) 
    {
        return false;
    }
    
    bool isConvOK{false};
    
    CoreContext::Id userId{userIdRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    CoreContext::Hash token             {tokenRawValue.toString()};
    QDateTime         creationDateTime  {creationDateTimeRawValue.toDateTime()};
    QDateTime         expirationDateTime{expirationDateTimeRawValue.toDateTime()};
    
    if (token.isEmpty() || !creationDateTime.isValid() || !expirationDateTime.isValid())
        return false;
    
    auto newSession = std::make_shared<EntitySession>(userId, token, expirationDateTime, creationDateTime);
    
    if (!newSession->isValid()) return false;
            
    entities.push_back(newSession);
    
    return true;
}

bool DatabaseEntityProcessorSQL::getEntityQuoteByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                                     std::vector<std::shared_ptr<EntityBase>> &entities)
{
    QSqlQuery sqlQuery{};
    
    if (!getQtSqlQueryByDatabaseQueryResultPtr(queryResult, sqlQuery))
        return false;
    
    auto idRawValue               = sqlQuery.value(EntityQuote::C_ID_PROP_NAME);
    auto textRawValue             = sqlQuery.value(EntityQuote::C_TEXT_PROP_NAME);
    auto authorRawValue           = sqlQuery.value(EntityQuote::C_AUTHOR_PROP_NAME);
    auto ratingRawValue           = sqlQuery.value(EntityQuote::C_RATING_PROP_NAME);
    auto creatorIdRawValue        = sqlQuery.value(EntityQuote::C_CREATOR_ID_PROP_NAME);
    auto creationDateTimeRawValue = sqlQuery.value(EntityQuote::C_CREATION_DATE_TIME_PROP_NAME);
    
    if (idRawValue.isNull() || textRawValue.isNull() || authorRawValue.isNull()
     || ratingRawValue.isNull() || creatorIdRawValue.isNull() || creationDateTimeRawValue.isNull())
    {
        return false;
    }
    
    bool isConvOK{false};
    
    CoreContext::Id id{idRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    QString text  {textRawValue.toString()};
    QString author{authorRawValue.toString()};
    
    if (text.isEmpty() || author.isEmpty()) return false;
    
    EntityQuote::Rating rating{ratingRawValue.toLongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    CoreContext::Id creatorId{creatorIdRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    QDateTime creationDateTime{creationDateTimeRawValue.toDateTime()};
    
    if (!creationDateTime.isValid()) return false;
    
    auto newQuote = std::make_shared<EntityQuote>(text, author, creatorId, creationDateTime, id, rating);
    
    if (!newQuote->isValid()) return false;
    
    entities.push_back(newQuote);
    
    return true;
}
