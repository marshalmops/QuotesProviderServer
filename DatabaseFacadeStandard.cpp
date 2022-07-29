#include "DatabaseFacadeStandard.h"

DatabaseFacadeStandard::DatabaseFacadeStandard(std::unique_ptr<DatabaseDriverStandard> &&driver, 
                                               std::unique_ptr<DatabaseEntityProcessorSQL> &&entityProcessor)
    : DatabaseFacadeBase{std::unique_ptr<DatabaseDriverBase>(dynamic_cast<DatabaseDriverBase*>(driver.release())), 
                         std::unique_ptr<DatabaseEntityProcessorSQL>(dynamic_cast<DatabaseEntityProcessorSQL*>(entityProcessor.release()))}
{
    
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::createUserSession(const std::unique_ptr<EntityUser> &userData, 
                                                                                   const std::unique_ptr<EntitySession> &sessionData,
                                                                                   std::unique_ptr<EntitySession> &createdSession)
{
    if (!userData->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    // selecting user...
    
    auto selectingUserByEmailCondition        = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityUser::C_EMAIL_PROP_NAME,    userData->getEmail());
    auto selectingUserByPasswordHashCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityUser::C_PASSWORD_PROP_NAME, userData->getPasswordHash());
    
    std::unique_ptr<DatabaseQueryBase> selectUserQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityUser::C_USER_TABLE_NAME},
                                                                                                     QStringList{},
                                                                                                     DatabaseQueryStandardSelect::ConditionsList{selectingUserByEmailCondition, selectingUserByPasswordHashCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectUserResults{};
    
    if (!m_driver->executeQuery(selectUserQuery, selectUserResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectUserResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    std::vector<std::shared_ptr<EntityBase>> selectedUsers{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_USER, selectUserResults.front(), selectedUsers))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if (selectedUsers.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto curUser = dynamic_cast<EntityUser*>(selectedUsers.front().get());
    
    if (!curUser)
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!curUser->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
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
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    // selecting inserted session: MB NOT?
    
    std::unique_ptr<EntitySession>           insertedSession{};
    DatabaseContext::DatabaseOperationResult selectSessionOperationResult{};
    
    if ((selectSessionOperationResult = getSessionByToken(sessionData->getToken(), insertedSession)) != DatabaseContext::DatabaseOperationResult::DOR_SUCCESS)
        return selectSessionOperationResult;
    
    if (!insertedSession->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    createdSession = std::make_unique<EntitySession>(userData->getId(), 
                                                     sessionData->getToken(),
                                                     sessionData->getExpirationDateTime(),
                                                     sessionData->getCreationDateTime());
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::createQuote(const std::unique_ptr<EntitySession> &session, 
                                                                             const std::unique_ptr<EntityQuote> &quoteData,
                                                                             std::unique_ptr<EntityQuote> &createdQuote)
{
    if (!session->isValid() || !quoteData->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    // selecting user by userId...
    
    auto selectingUserByIdCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityUser::C_ID_PROP_NAME, session->getUserId());
    
    std::unique_ptr<DatabaseQueryBase> selectUserQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityUser::C_USER_TABLE_NAME},
                                                                                                     QStringList{},
                                                                                                     DatabaseQueryStandardSelect::ConditionsList{selectingUserByIdCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectUserResults{};
    
    if (!m_driver->executeQuery(selectUserQuery, selectUserResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectUserResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    std::vector<std::shared_ptr<EntityBase>> selectedUsers{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_USER, selectUserResults.front(), selectedUsers))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if (selectedUsers.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    auto curUser = dynamic_cast<EntityUser*>(selectedUsers.front().get());
    
    if (!curUser) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!curUser->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    // inserting quote...
    
    QStringList insertingQuoteAttributes{EntityQuote::C_TEXT_PROP_NAME, 
                                         EntityQuote::C_AUTHOR_PROP_NAME,
                                         EntityQuote::C_RATING_PROP_NAME,
                                         EntityQuote::C_CREATOR_ID_PROP_NAME,
                                         EntityQuote::C_CREATION_DATE_TIME_PROP_NAME};
    
    DatabaseQueryStandardInsert::ValuesList insertingQuoteValues{quoteData->getText(),
                                                                 quoteData->getAuthor(),
                                                                 quoteData->getRating(),
                                                                 curUser->getId(),
                                                                 quoteData->getCreationDateTime()};
    
    std::unique_ptr<DatabaseQueryBase> insertQuoteQuery{std::make_unique<DatabaseQueryStandardInsert>(EntityQuote::C_QUOTE_TABLE_NAME, 
                                                                                                        insertingQuoteValues, 
                                                                                                        insertingQuoteAttributes)};
     
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> insertResults{};
    
    if (!m_driver->executeQuery(insertQuoteQuery, insertResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    // selecting inserted quote by id, text and creationDateTime...
    
    auto selectingQuoteByIdCondition               = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityQuote::C_CREATOR_ID_PROP_NAME,         curUser->getId());
    auto selectingQuoteByTextCondition             = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityQuote::C_TEXT_PROP_NAME,               quoteData->getText());
    auto selectingQuoteByCreationDataTimeCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityQuote::C_CREATION_DATE_TIME_PROP_NAME, quoteData->getCreationDateTime());
    
    std::unique_ptr<DatabaseQueryBase> selectQuoteQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityQuote::C_QUOTE_TABLE_NAME},
                                                                                                      QStringList{},
                                                                                                      DatabaseQueryStandardSelect::ConditionsList{selectingQuoteByIdCondition, selectingQuoteByTextCondition, selectingQuoteByCreationDataTimeCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectQuoteResults{};
    
    if (!m_driver->executeQuery(selectQuoteQuery, selectQuoteResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectQuoteResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    std::vector<std::shared_ptr<EntityBase>> selectedQuotes{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_QUOTE, selectQuoteResults.front(), selectedQuotes))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if (selectedQuotes.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    if (!selectedQuotes.front()->isValid())
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto curQuote = dynamic_cast<EntityQuote*>(selectedQuotes.front().get());
    
    if (!curQuote) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!curQuote->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    createdQuote = std::make_unique<EntityQuote>(std::move(*curQuote));
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::getQuoteById(const CoreContext::Id quoteId,
                                                                              std::unique_ptr<EntityQuote> &gottenQuote)
{
    auto selectingQuoteByIdCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityQuote::C_ID_PROP_NAME, quoteId);
    
    std::unique_ptr<DatabaseQueryBase> selectQuoteQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityQuote::C_QUOTE_TABLE_NAME},
                                                                                                      QStringList{},
                                                                                                      DatabaseQueryStandardSelect::ConditionsList{selectingQuoteByIdCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectQuoteResults{};
    
    if (!m_driver->executeQuery(selectQuoteQuery, selectQuoteResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectQuoteResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    std::vector<std::shared_ptr<EntityBase>> selectedQuotes{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_QUOTE, selectQuoteResults.front(), selectedQuotes))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if (selectedQuotes.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    if (!selectedQuotes.front()->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto curQuote = dynamic_cast<EntityQuote*>(selectedQuotes.front().get());
    
    if (!curQuote) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!curQuote->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    gottenQuote = std::make_unique<EntityQuote>(std::move(*curQuote));
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::getQuotesCount(CoreContext::Id &quotesCount)
{
    std::unique_ptr<DatabaseQueryBase> selectQuoteQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityQuote::C_QUOTE_TABLE_NAME},
                                                                                                      QStringList{QString{"MAX("} + EntityQuote::C_ID_PROP_NAME + ")"},
                                                                                                      DatabaseQueryStandardSelect::ConditionsList{})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectQuoteResults{};
    
    if (!m_driver->executeQuery(selectQuoteQuery, selectQuoteResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectQuoteResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    DatabaseQueryResultStandard *quoteQueryResult{dynamic_cast<DatabaseQueryResultStandard*>(selectQuoteResults.front().get())};
    
    DatabaseContext::DatabaseOperationResult gettingQuoteOperationResult{};
    QVariant quoteIdRawValue{};
    
    if ((gettingQuoteOperationResult = getQueryResultPropValue(quoteQueryResult, EntityQuote::C_ID_PROP_NAME, quoteIdRawValue)) != DatabaseContext::DatabaseOperationResult::DOR_SUCCESS)
        return gettingQuoteOperationResult;
    
    bool isConvOK{false};
    
    CoreContext::Id quotesCountBuffer{quoteIdRawValue.toULongLong(&isConvOK)};
    
    if (!isConvOK) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    quotesCount = quotesCountBuffer;
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::createGradeForQuote(const std::unique_ptr<EntityGrade> &gradeData,
                                                                                     std::unique_ptr<EntityGrade> &createdGrade)
{
    if (!gradeData->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    DatabaseContext::DatabaseOperationResult selectingGradeOperationResult{};
    std::unique_ptr<EntityGrade> selectedGrade{};
    
    if ((selectingGradeOperationResult = getGradeByQuoteIdAndDeviceHash(gradeData->getQuoteId(), gradeData->getDeviceHash(), selectedGrade)) != DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND) {
        return (selectingGradeOperationResult == DatabaseContext::DatabaseOperationResult::DOR_SUCCESS
              ? DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND
              : selectingGradeOperationResult);
    }
    
    std::unique_ptr<EntityQuote> selectedQuote{};
    
    if ((selectingGradeOperationResult = getQuoteById(gradeData->getQuoteId(), selectedQuote)) != DatabaseContext::DatabaseOperationResult::DOR_SUCCESS)
        return selectingGradeOperationResult;
    if (!selectedQuote.get()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!selectedQuote->isValid())
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    QStringList insertingGradeAttributes{EntityGrade::C_QUOTE_ID_PROP_NAME, 
                                         EntityGrade::C_DEVICE_HASH_PROP_NAME,
                                         EntityGrade::C_GRADE_PROP_NAME};
    
    DatabaseQueryStandardInsert::ValuesList insertingGradeValues{gradeData->getQuoteId(),
                                                                 gradeData->getDeviceHash(),
                                                                 gradeData->getGrade()};
    
    std::unique_ptr<DatabaseQueryBase> insertGradeQuery{std::make_unique<DatabaseQueryStandardInsert>(EntityGrade::C_GRADE_TABLE_NAME, 
                                                                                                      insertingGradeValues, 
                                                                                                      insertingGradeAttributes)};
     
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> insertResults{};
    
    if (!m_driver->executeQuery(insertGradeQuery, insertResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if ((selectingGradeOperationResult = getGradeByQuoteIdAndDeviceHash(gradeData->getQuoteId(), gradeData->getDeviceHash(), selectedGrade)) != DatabaseContext::DatabaseOperationResult::DOR_SUCCESS)
        return selectingGradeOperationResult;
    
    QStringList                             updateAttributes{EntityQuote::C_RATING_PROP_NAME};
    DatabaseQueryStandardUpdate::ValuesList updateValues    {selectedQuote->getRating() + gradeData->getGrade()};
    auto                                    updateCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO,
                                                                                                               EntityGrade::C_QUOTE_ID_PROP_NAME,
                                                                                                               gradeData->getQuoteId());
    
    std::unique_ptr<DatabaseQueryBase> updateQuoteRatingQuery{std::make_unique<DatabaseQueryStandardUpdate>(QStringList{EntityQuote::C_QUOTE_TABLE_NAME},
                                                                                                            updateAttributes,
                                                                                                            updateValues,
                                                                                                            DatabaseQueryStandardUpdate::ConditionsList{updateCondition})};
    
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> updateResults{};
    
    if (!m_driver->executeQuery(updateQuoteRatingQuery, updateResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    createdGrade = std::move(selectedGrade);
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::getSessionByToken(const CoreContext::Hash &token, 
                                                                                   std::unique_ptr<EntitySession> &gottenSession)
{
    if (token.isEmpty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto selectingSessionByTokenCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntitySession::C_TOKEN_PROP_NAME, token);
    
    std::unique_ptr<DatabaseQueryBase> selectSessionQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntitySession::C_SESSION_TABLE_NAME},
                                                                                                        QStringList{},
                                                                                                        DatabaseQueryStandardSelect::ConditionsList{selectingSessionByTokenCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectSessionResults{};
    
    if (!m_driver->executeQuery(selectSessionQuery, selectSessionResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectSessionResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    std::vector<std::shared_ptr<EntityBase>> selectedSessions{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_SESSION, selectSessionResults.front(), selectedSessions))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if (selectedSessions.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    auto curSession = dynamic_cast<EntitySession*>(selectedSessions.front().get());
    
    if (!curSession)            
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!curSession->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    gottenSession = std::make_unique<EntitySession>(std::move(*curSession));
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::removeSessionByToken(const CoreContext::Hash &token)
{
    if (token.isEmpty())
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto selectingGradeByQuoteIdCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntitySession::C_TOKEN_PROP_NAME, token);
    
    std::unique_ptr<DatabaseQueryBase> deleteSessionQuery{std::make_unique<DatabaseQueryStandardDelete>(EntitySession::C_SESSION_TABLE_NAME,
                                                                                                        DatabaseQueryStandardDelete::ConditionsList{selectingGradeByQuoteIdCondition})};
    
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> deleteSessionQueryResults{};
    
    if (!m_driver->executeQuery(deleteSessionQuery, deleteSessionQueryResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::getGradeByQuoteIdAndDeviceHash(const CoreContext::Id quoteId,
                                                                                                const CoreContext::Hash &deviceHash,
                                                                                                std::unique_ptr<EntityGrade> &gottenGrade)
{
    if (deviceHash.isEmpty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto selectingGradeByQuoteIdCondition    = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityGrade::C_QUOTE_ID_PROP_NAME,    quoteId);
    auto selectingGradeByDeviceHashCondition = std::make_shared<DatabaseQueryConditionStandard>(DatabaseQueryContextStandard::DatabaseQueryConditionType::DQCT_EQUAL_TO, EntityGrade::C_DEVICE_HASH_PROP_NAME, deviceHash);    
    
    std::unique_ptr<DatabaseQueryBase> selectGradeQuery{std::make_unique<DatabaseQueryStandardSelect>(QStringList{EntityGrade::C_GRADE_TABLE_NAME},
                                                                                                      QStringList{},
                                                                                                      DatabaseQueryStandardSelect::ConditionsList{selectingGradeByQuoteIdCondition, selectingGradeByDeviceHashCondition})};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> selectGradeResults{};
    
    if (!m_driver->executeQuery(selectGradeQuery, selectGradeResults))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (selectGradeResults.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    std::vector<std::shared_ptr<EntityBase>> selectedGrades{};
    
    if (!m_entityProcessor->getEntityByDatabaseQueryResult(CoreContext::EntityType::ET_GRADE, selectGradeResults.front(), selectedGrades))
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    if (selectedGrades.empty()) 
        return DatabaseContext::DatabaseOperationResult::DOR_NOT_FOUND;
    
    auto curGrade = dynamic_cast<EntityGrade*>(selectedGrades.front().get());
    
    if (!curGrade)            
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    if (!curGrade->isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    gottenGrade = std::make_unique<EntityGrade>(std::move(*curGrade));
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}

DatabaseContext::DatabaseOperationResult DatabaseFacadeStandard::getQueryResultPropValue(const DatabaseQueryResultStandard *queryResult,
                                                                                            const QString &propName, 
                                                                                            QVariant &propValue)
{
    if (propName.isEmpty() || !queryResult) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    auto sqlResult = queryResult->getSqlResult();
    
    if (!sqlResult.isValid()) 
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    QVariant propValueBuffer{};
    
    if (!(propValueBuffer = sqlResult.value(propName)).isValid())
        return DatabaseContext::DatabaseOperationResult::DOR_ERROR;
    
    propValue = std::move(propValueBuffer);
    
    return DatabaseContext::DatabaseOperationResult::DOR_SUCCESS;
}
