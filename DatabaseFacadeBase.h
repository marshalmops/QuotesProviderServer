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
    
    virtual bool createUserSession  (const std::unique_ptr<EntityUser> &userData,
                                     const std::unique_ptr<EntitySession> &sessionData,
                                     std::unique_ptr<EntitySession> &createdSession) = 0;
    virtual bool createQuote        (const CoreContext::Hash &token,
                                     const std::unique_ptr<EntitySession> &quoteData,
                                     std::unique_ptr<EntitySession> &createdQuote) = 0;
    virtual bool getQuoteById       (const CoreContext::Id quoteId,
                                     std::unique_ptr<EntitySession> &gottenQuote) = 0;
    virtual bool getQuotesCount     (CoreContext::Id &quotesCount) = 0;
    virtual bool createGradeForQuote(const std::unique_ptr<EntityGrade> &gradeData,
                                     std::unique_ptr<EntityGrade> &createdGrade) = 0;
    
protected:
    std::unique_ptr<DatabaseDriverBase>               m_driver;
    std::unique_ptr<DatabaseEntityProcessorInterface> m_entityProcessor;
};

#endif // DATABASEFACADEBASE_H
