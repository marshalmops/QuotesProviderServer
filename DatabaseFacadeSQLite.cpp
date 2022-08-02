#include "DatabaseFacadeSQLite.h"

DatabaseFacadeSQLite::DatabaseFacadeSQLite(std::unique_ptr<DatabaseDriverSQLite> &&driver,
                                           std::unique_ptr<DatabaseEntityProcessorSQL> &&entityProcessor)
    : DatabaseFacadeStandard{std::unique_ptr<DatabaseDriverStandard>(dynamic_cast<DatabaseDriverStandard*>(driver.release())),
                             std::move(entityProcessor)}
{
    
}

bool DatabaseFacadeSQLite::initializeTables()
{
    QString creationQueryString{};
    std::vector<std::shared_ptr<DatabaseQueryResultBase>> results{};
    
    creationQueryString += QString("CREATE TABLE ") + EntityGrade::C_GRADE_TABLE_NAME + '(';
    creationQueryString += QString(EntityGrade::C_QUOTE_ID_PROP_NAME) + " INTEGER NOT NULL,";
    creationQueryString += QString(EntityGrade::C_DEVICE_HASH_PROP_NAME) + " VARCHAR(511) NOT NULL,";
    creationQueryString += QString(EntityGrade::C_GRADE_PROP_NAME) + " INTEGER NOT NULL);";
    
    if (!m_driver->executeRawQuery(creationQueryString, results))
        return false;
    
    creationQueryString.clear();
    
    creationQueryString += QString("CREATE TABLE ") + EntityQuote::C_QUOTE_TABLE_NAME + '(';
    creationQueryString += QString(EntityQuote::C_ID_PROP_NAME) + " INTEGER PRIMARY KEY AUTOINCREMENT,";
    creationQueryString += QString(EntityQuote::C_TEXT_PROP_NAME) + " NVARCHAR(2047) NOT NULL,";
    creationQueryString += QString(EntityQuote::C_TEXT_HASH_PROP_NAME) + " VARCHAR(511) NOT NULL,";
    creationQueryString += QString(EntityQuote::C_AUTHOR_PROP_NAME) + " NVARCHAR(511) NOT NULL,";
    creationQueryString += QString(EntityQuote::C_CREATOR_ID_PROP_NAME) + " INTEGER NOT NULL,";    
    creationQueryString += QString(EntityQuote::C_CREATION_DATE_TIME_PROP_NAME) + " DATE NOT NULL);";
    
    if (!m_driver->executeRawQuery(creationQueryString, results))
        return false;
    
    creationQueryString.clear();
    
    creationQueryString += QString("CREATE TABLE ") + EntitySession::C_SESSION_TABLE_NAME + '(';
    creationQueryString += QString(EntitySession::C_ID_PROP_NAME) + " INTEGER NOT NULL,";
    creationQueryString += QString(EntitySession::C_TOKEN_PROP_NAME) + " VARCHAR(511) NOT NULL,";
    creationQueryString += QString(EntitySession::C_CREATION_DATE_TIME_PROP_NAME) + " DATE NOT NULL,";    
    creationQueryString += QString(EntitySession::C_EXPIRATION_DATE_TIME_PROP_NAME) + " DATE NOT NULL);";
    
    if (!m_driver->executeRawQuery(creationQueryString, results))
        return false;
    
    creationQueryString.clear();
    
    creationQueryString += QString("CREATE TABLE ") + EntityUser::C_USER_TABLE_NAME + '(';
    creationQueryString += QString(EntityUser::C_ID_PROP_NAME) + " INTEGER PRIMARY KEY AUTOINCREMENT,";
    creationQueryString += QString(EntityUser::C_EMAIL_PROP_NAME) + " VARCHAR(127) NOT NULL,";
    creationQueryString += QString(EntityUser::C_PASSWORD_PROP_NAME) + " NVARCHAR(127) NOT NULL);";
    
    return (m_driver->executeRawQuery(creationQueryString, results));
}
