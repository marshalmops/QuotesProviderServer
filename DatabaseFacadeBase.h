#ifndef DATABASEFACADEBASE_H
#define DATABASEFACADEBASE_H

#include "DatabaseDriverBase.h"

#include "DatabaseEntityProcessorInterface.h"

#include "EntityGrade.h"
#include "EntityQuote.h"
#include "EntitySession.h"
#include "EntityUser.h"

class DatabaseFacadeBase
{
public:
    DatabaseFacadeBase(std::unique_ptr<DatabaseDriverBase> &&driver,
                       std::unique_ptr<DatabaseEntityProcessorInterface> &&entityProcessor);
    virtual ~DatabaseFacadeBase() = default;
    
    virtual bool testDatabaseCorrectness() = 0;
    virtual bool initializeTables       () = 0;
    
    virtual DatabaseContext::DatabaseOperationResult createUserSession  (const std::unique_ptr<EntityUser> &userData,
                                                                         const std::unique_ptr<EntitySession> &sessionData,
                                                                         std::unique_ptr<EntitySession> &createdSession) = 0;
    virtual DatabaseContext::DatabaseOperationResult createQuote        (const std::unique_ptr<EntitySession> &session,
                                                                         const std::unique_ptr<EntityQuote> &quoteData,
                                                                         std::unique_ptr<EntityQuote> &createdQuote) = 0;
    virtual DatabaseContext::DatabaseOperationResult getQuoteById       (const CoreContext::Id quoteId,
                                                                         std::unique_ptr<EntityQuote> &gottenQuote) = 0;
    virtual DatabaseContext::DatabaseOperationResult getQuotesCount     (CoreContext::Id &quotesCount) = 0;
    virtual DatabaseContext::DatabaseOperationResult createGradeForQuote(const std::unique_ptr<EntityGrade> &gradeData,
                                                                         std::unique_ptr<EntityGrade> &createdGrade) = 0;
    
    virtual DatabaseContext::DatabaseOperationResult getSessionByToken   (const CoreContext::Hash &token,
                                                                          std::unique_ptr<EntitySession> &gottenSession) = 0;
    virtual DatabaseContext::DatabaseOperationResult removeSessionByToken(const CoreContext::Hash &token) = 0;
    
protected:
    std::unique_ptr<DatabaseDriverBase>               m_driver;
    std::unique_ptr<DatabaseEntityProcessorInterface> m_entityProcessor;
};

#endif // DATABASEFACADEBASE_H
