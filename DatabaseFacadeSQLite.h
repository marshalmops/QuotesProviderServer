#ifndef DATABASEFACADESQLITE_H
#define DATABASEFACADESQLITE_H

#include "DatabaseDriverSQLite.h"
#include "DatabaseFacadeStandard.h"

class DatabaseFacadeSQLite : public DatabaseFacadeStandard
{
public:
    DatabaseFacadeSQLite(std::unique_ptr<DatabaseDriverSQLite> &&driver,
                         std::unique_ptr<DatabaseEntityProcessorSQL> &&entityProcessor);
    
    virtual bool initializeTables() override;
};

#endif // DATABASEFACADESQLITE_H
