#ifndef DATABASEFACADESTANDARD_H
#define DATABASEFACADESTANDARD_H

#include "DatabaseFacadeBase.h"

#include "DatabaseDriverStandard.h"
#include "DatabaseEntityProcessorSQL.h"

#include "DatabaseQueryStandardSelect.h"
#include "DatabaseQueryStandardInsert.h"
#include "DatabaseQueryStandardUpdate.h"
#include "DatabaseQueryStandardDelete.h"

class DatabaseFacadeStandard : public DatabaseFacadeBase
{
public:
    DatabaseFacadeStandard(std::unique_ptr<DatabaseDriverStandard> &&driver,
                           std::unique_ptr<DatabaseEntityProcessorSQL> &&entityProcessor);
    
    virtual bool createUserSession  (const std::unique_ptr<EntityUser> &userData,
                                     const std::unique_ptr<EntitySession> &sessionData,
                                     std::unique_ptr<EntitySession> &createdSession) override;
    virtual bool createQuote        (const CoreContext::Hash &token,
                                     const std::unique_ptr<EntitySession> &quoteData, 
                                     std::unique_ptr<EntitySession> &createdQuote) override;
    virtual bool getQuoteById       (const CoreContext::Id quoteId, 
                                     std::unique_ptr<EntitySession> &gottenQuote) override;
    virtual bool getQuotesCount     (CoreContext::Id &quotesCount) override;
    virtual bool createGradeForQuote(const std::unique_ptr<EntityGrade> &gradeData, 
                                     std::unique_ptr<EntityGrade> &createdGrade) override;
};

#endif // DATABASEFACADESTANDARD_H
