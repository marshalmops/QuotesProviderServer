#include "DatabaseFacadeStandard.h"

DatabaseFacadeStandard::DatabaseFacadeStandard(std::unique_ptr<DatabaseDriverStandard> &&driver, 
                                               std::unique_ptr<DatabaseEntityProcessorSQL> &&entityProcessor)
    : DatabaseFacadeBase{std::unique_ptr<DatabaseDriverBase>(dynamic_cast<DatabaseDriverBase*>(driver.release())), 
                         std::unique_ptr<DatabaseEntityProcessorSQL>(dynamic_cast<DatabaseEntityProcessorSQL*>(entityProcessor.release()))}
{
    
}

bool DatabaseFacadeStandard::createUserSession(const std::unique_ptr<EntityUser> &userData, 
                                               const std::unique_ptr<EntitySession> &sessionData,
                                               std::unique_ptr<EntitySession> &createdSession)
{
    if (!userData->isValid()) return false;
    
    auto selectingUserByEmailCondition        = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityUser::C_EMAIL_PROP_NAME,    userData->getEmail());
    auto selectingUserByPasswordHashCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityUser::C_PASSWORD_PROP_NAME, userData->getPasswordHash());
    
    std::unique_ptr<DatabaseQueryBase> selectUserQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityUser::C_USER_TABLE_NAME},
                                                                                                     QStringList{},
                                                                                                     DatabaseQueryStandardSelect::ConditionsList{selectingUserByEmailCondition, selectingUserByPasswordHashCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectUserResults{};
    
    if (!m_driver->executeQuery(selectUserQuery, selectUserResults))
        return false;
    if (selectUserResults.empty()) return false;
    
    std::vector<std::shared_ptr<EntityBase>> selectedUsers{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_USER, selectUserResults.front(), selectedUsers))
        return false;
    
    if (selectedUsers.empty())             return false;
    if (!selectedUsers.front()->isValid()) return false;
    
    auto curUser = dynamic_cast<EntityUser*>(selectedUsers.front().get());
    
    if (!curUser) return false;
    
    // session creation:
    
    QStringList insertingSessionAttributes{EntitySession::C_ID_PROP_NAME,
                                           EntitySession::C_TOKEN_PROP_NAME, 
                                           EntitySession::C_CREATION_DATE_TIME_PROP_NAME,
                                           EntitySession::C_EXPIRATION_DATE_TIME_PROP_NAME};
    
    DatabaseQueryStandardInsert::ValuesList insertingSessionValues{curUser->getId(),
                                                                   sessionData->getToken(),
                                                                   sessionData->getCreationDateTime(),
                                                                   sessionData->getExpirationDateTime()};
    
    std::unique_ptr<DatabaseQueryBase> insertSessionQuery{std::make_unique<DatabaseQueryStandardInsert>(EntitySession::C_SESSION_TABLE_NAME, 
                                                                                                        insertingSessionValues, 
                                                                                                        insertingSessionAttributes)};
     
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> insertResults{};
    
    if (!m_driver->executeQuery(insertSessionQuery, insertResults))
        return false;
    
    // getting inserted data:
    
    auto selectingSessionByTokenCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntitySession::C_TOKEN_PROP_NAME, sessionData->getToken());
    
    std::unique_ptr<DatabaseQueryBase> selectSessionQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntitySession::C_SESSION_TABLE_NAME},
                                                                                                        QStringList{EntitySession::C_TOKEN_PROP_NAME},
                                                                                                        DatabaseQueryStandardSelect::ConditionsList{selectingSessionByTokenCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectSessionResults{};
    
    if (!m_driver->executeQuery(selectSessionQuery, selectSessionResults))
        return false;
    if (selectSessionResults.empty()) return false;
    
    createdSession = std::make_unique<EntitySession>(userData->getId(), 
                                                     sessionData->getToken(),
                                                     sessionData->getExpirationDateTime(),
                                                     sessionData->getCreationDateTime());
    
    return true;
}

bool DatabaseFacadeStandard::createQuote(const CoreContext::Hash &token, 
                                         const std::unique_ptr<EntitySession> &quoteData,
                                         std::unique_ptr<EntitySession> &createdQuote)
{
    
}

bool DatabaseFacadeStandard::getQuoteById(const CoreContext::Id quoteId,
                                          std::unique_ptr<EntitySession> &gottenQuote)
{
    
}

bool DatabaseFacadeStandard::getQuotesCount(CoreContext::Id &quotesCount)
{
    
}

bool DatabaseFacadeStandard::createGradeForQuote(const std::unique_ptr<EntityGrade> &gradeData,
                                                 std::unique_ptr<EntityGrade> &createdGrade)
{
    
}
