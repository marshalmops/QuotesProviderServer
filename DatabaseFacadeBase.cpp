#include "DatabaseFacadeBase.h"

DatabaseFacadeBase::DatabaseFacadeBase(std::unique_ptr<DatabaseDriverBase> &&driver,
                                       std::unique_ptr<DatabaseEntityProcessorInterface> &&entityProcessor)
    : m_driver{driver.release()},
      m_entityProcessor{entityProcessor.release()}
{
    
}
