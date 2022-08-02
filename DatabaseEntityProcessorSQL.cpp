#include "DatabaseEntityProcessorSQL.h"

namespace {

bool getQtSqlRecordByDatabaseQueryResultPtr(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                           QSqlRecord &sqlRecord)
{
    DatabaseQueryResultStandard *queryResultSQL = dynamic_cast<DatabaseQueryResultStandard*>(queryResult.get());
    
    if (!queryResultSQL) return false;
    
    sqlRecord = queryResultSQL->getSqlResult();
    
    return true;
}

}

bool DatabaseEntityProcessorSQL::getEntityGradeByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                                     std::vector<std::shared_ptr<EntityBase>> &entities)
{
    QSqlRecord sqlRecord{};
    
    if (!getQtSqlRecordByDatabaseQueryResultPtr(queryResult, sqlRecord))
        return false;
    
    auto quoteIdRawValue    = sqlRecord.value(EntityGrade::C_QUOTE_ID_PROP_NAME);
    auto deviceHashRawValue = sqlRecord.value(EntityGrade::C_DEVICE_HASH_PROP_NAME);
    auto gradeRawValue      = sqlRecord.value(EntityGrade::C_GRADE_PROP_NAME);
    
    if (quoteIdRawValue.isNull() || deviceHashRawValue.isNull() || gradeRawValue.isNull())
        return false;
    
    bool isConvOK{false};
    
    CoreContext::Id quoteId{quoteIdRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    CoreContext::Hash deviceHash{deviceHashRawValue.toString()};
    CoreContext::QuoteGrade grade{static_cast<CoreContext::QuoteGrade>(gradeRawValue.toInt(&isConvOK))};
    
    if (!isConvOK || deviceHash.isEmpty()) return false;
    
    auto newGrade = std::make_shared<EntityGrade>(quoteId, deviceHash, grade);
    
    if (!newGrade->isValid()) return false;
    
    entities.push_back(newGrade);
    
    return true;
}

bool DatabaseEntityProcessorSQL::getEntityUserByDatabaseQueryResult(const std::shared_ptr<DatabaseQueryResultBase> &queryResult,
                                                                    std::vector<std::shared_ptr<EntityBase>> &entities)
{
    QSqlRecord sqlRecord{};
    
    if (!getQtSqlRecordByDatabaseQueryResultPtr(queryResult, sqlRecord))
        return false;
    
    auto idRawValue       = sqlRecord.value(EntityUser::C_ID_PROP_NAME);
    auto emailRawValue    = sqlRecord.value(EntityUser::C_EMAIL_PROP_NAME);
    auto passwordRawValue = sqlRecord.value(EntityUser::C_PASSWORD_PROP_NAME);
    
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
    QSqlRecord sqlRecord{};
    
    if (!getQtSqlRecordByDatabaseQueryResultPtr(queryResult, sqlRecord))
        return false;
    
    auto userIdRawValue             = sqlRecord.value(EntitySession::C_ID_PROP_NAME);
    auto tokenRawValue              = sqlRecord.value(EntitySession::C_TOKEN_PROP_NAME);
    auto creationDateTimeRawValue   = sqlRecord.value(EntitySession::C_CREATION_DATE_TIME_PROP_NAME);
    auto expirationDateTimeRawValue = sqlRecord.value(EntitySession::C_EXPIRATION_DATE_TIME_PROP_NAME);
    
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
    QSqlRecord sqlRecord{};
    
    if (!getQtSqlRecordByDatabaseQueryResultPtr(queryResult, sqlRecord))
        return false;
    
    auto idRawValue               = sqlRecord.value(EntityQuote::C_ID_PROP_NAME);
    auto textRawValue             = sqlRecord.value(EntityQuote::C_TEXT_PROP_NAME);
    auto textHashRawValue         = sqlRecord.value(EntityQuote::C_TEXT_HASH_PROP_NAME);
    auto authorRawValue           = sqlRecord.value(EntityQuote::C_AUTHOR_PROP_NAME);
    auto creatorIdRawValue        = sqlRecord.value(EntityQuote::C_CREATOR_ID_PROP_NAME);
    auto creationDateTimeRawValue = sqlRecord.value(EntityQuote::C_CREATION_DATE_TIME_PROP_NAME);
    
    if (idRawValue.isNull() || textRawValue.isNull() || textHashRawValue.isNull() || authorRawValue.isNull()
     || creatorIdRawValue.isNull() || creationDateTimeRawValue.isNull())
    {
        return false;
    }
    
    bool isConvOK{false};
    
    CoreContext::Id id{idRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    QString           text    {textRawValue.toString()};
    CoreContext::Hash textHash{textHashRawValue.toString()};
    QString           author  {authorRawValue.toString()};
    
    if (text.isEmpty() || author.isEmpty() || textHash.isEmpty()) return false;
    
    CoreContext::Id creatorId{creatorIdRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) return false;
    
    QDateTime creationDateTime{creationDateTimeRawValue.toDateTime()};
    
    if (!creationDateTime.isValid()) return false;
    
    auto newQuote = std::make_shared<EntityQuote>(text, author, textHash, creationDateTime, creatorId, id);
    
    if (!newQuote->isValid()) return false;
    
    entities.push_back(newQuote);
    
    return true;
}
