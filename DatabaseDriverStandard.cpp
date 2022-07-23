#include "DatabaseDriverStandard.h"

DatabaseDriverStandard::DatabaseDriverStandard(const QString &connectionName,
                                               std::unique_ptr<DatabaseQueryParserStandard> &&queryParser)
    : DatabaseDriverBase{std::unique_ptr<DatabaseQueryParserInterface>(queryParser.release())},
      m_connectionName{connectionName}
{
    
}
