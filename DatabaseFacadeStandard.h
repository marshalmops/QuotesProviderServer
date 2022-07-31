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
    
    virtual bool testDatabaseCorrectness() override;
    virtual bool initializeTables       () override;
    
    virtual DatabaseContext::DatabaseOperationResult createUserSession  (const std::unique_ptr<EntityUser> &userData,
                                                                         const std::unique_ptr<EntitySession> &sessionData,
                                                                         std::unique_ptr<EntitySession> &createdSession) override;
    virtual DatabaseContext::DatabaseOperationResult createQuote        (const std::unique_ptr<EntitySession> &session,
                                                                         const std::unique_ptr<EntityQuote> &quoteData, 
                                                                         std::unique_ptr<EntityQuote> &createdQuote) override;
    virtual DatabaseContext::DatabaseOperationResult getQuoteById       (const CoreContext::Id quoteId, 
                                                                         std::unique_ptr<EntityQuote> &gottenQuote) override;
    virtual DatabaseContext::DatabaseOperationResult getQuotesCount     (CoreContext::Id &quotesCount) override;
    virtual DatabaseContext::DatabaseOperationResult createGradeForQuote(const std::unique_ptr<EntityGrade> &gradeData, 
                                                                         std::unique_ptr<EntityGrade> &createdGrade) override;
    
    virtual DatabaseContext::DatabaseOperationResult getSessionByToken   (const CoreContext::Hash &token,
                                                                          std::unique_ptr<EntitySession> &gottenSession) override;
    virtual DatabaseContext::DatabaseOperationResult removeSessionByToken(const CoreContext::Hash &token) override;
    
protected:
    DatabaseContext::DatabaseOperationResult getGradeByQuoteIdAndDeviceHash(const CoreContext::Id quoteId,
                                                                            const CoreContext::Hash &deviceHash,
                                                                            std::unique_ptr<EntityGrade> &gottenGrade);
   
    DatabaseContext::DatabaseOperationResult getQueryResultPropValue(const DatabaseQueryResultStandard *queryResult,
                                                                     const QString &propName,
                                                                     QVariant &propValue);
};

#endif // DATABASEFACADESTANDARD_H
