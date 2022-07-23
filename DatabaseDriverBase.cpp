#include "DatabaseDriverBase.h"

DatabaseDriverBase::DatabaseDriverBase(std::unique_ptr<DatabaseQueryParserInterface> &&queryParser)
    : m_queryParser{queryParser.release()}
{
    
}
