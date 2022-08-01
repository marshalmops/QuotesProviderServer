#include "DatabaseQueryParserStandard.h"


bool DatabaseQueryParserStandard::parseQuery(const std::unique_ptr<DatabaseQueryBase> &query,
                                             std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    if (!query->isValid()) return false;
    
    switch (query->getType()) {
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_SELECT: {return parseSelectQuery(dynamic_cast<DatabaseQueryStandardSelect*>(query.get()), result);}
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_INSERT: {return parseInsertQuery(dynamic_cast<DatabaseQueryStandardInsert*>(query.get()), result);}
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_UPDATE: {return parseUpdateQuery(dynamic_cast<DatabaseQueryStandardUpdate*>(query.get()), result);}
    case DatabaseQueryContextStandard::DatabaseQueryType::DQT_DELETE: {return parseDeleteQuery(dynamic_cast<DatabaseQueryStandardDelete*>(query.get()), result);}
    }
    
    return false;
}

bool DatabaseQueryParserStandard::parseSelectQuery(const DatabaseQueryStandardSelect * const query,
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    if (!query) return false;
    
    QString sqlString{};
    
    sqlString += "SELECT ";
    
    auto attributesCount = query->getAttributes().length();
    
    if (attributesCount == 0) {
        sqlString += "* ";
        
    } else {
        for (auto i = 0; i < attributesCount; ++i) {
            sqlString += (query->getAttributes().at(i) + (i + 1 == attributesCount ? ' ' : ','));
        }
    }
    
    sqlString += "FROM ";
    
    auto tablesCount = query->getTables().length();
    
    for (auto i = 0; i < tablesCount; ++i) {
        sqlString += (query->getTables().at(i) + (i + 1 == tablesCount ? ' ' : ','));
    }
    
    if (!query->getConditions().empty()) {
        QString conditionsString{conditionsListToString(query->getConditions())};
        
        if (conditionsString.isEmpty()) 
            return false;
        
        sqlString += conditionsString;
    }
    
    auto orderingPairsCount = query->getOrderingPairs().size();
    
    if (orderingPairsCount > 0) {
        sqlString += ("ORDER BY ");
        
        for (auto i = 0; i < orderingPairsCount; ++i) {
            sqlString += (query->getOrderingPairs().at(i).second + " ");
            sqlString += (orderFlagToString(query->getOrderingPairs().at(i).first));
            sqlString += (i + 1 == orderingPairsCount ? ' ' : ',');
        }
    }
    
    if (query->getLimit() != 0) {
        sqlString += ("LIMIT " + QString::number(query->getLimit()));
    }
    
    sqlString += ';';
    
    result = std::make_unique<DatabaseQueryParserResultSQL>(sqlString);
    
    return true;
}

bool DatabaseQueryParserStandard::parseInsertQuery(const DatabaseQueryStandardInsert * const query,
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    if (!query) return false;
    
    QString sqlString{};
    
    sqlString += "INSERT INTO ";
    sqlString += query->getTables().front();
    
    auto attributesCount = query->getAttributes().length();
    
    if (attributesCount != 0) {
        sqlString += '(';
        
        for (auto i = 0; i < attributesCount; ++i) {
            sqlString += (query->getAttributes().at(i) + (i + 1 == attributesCount ? ") " : ","));
        }
    }
    
    sqlString += "VALUES (";
    
    auto valuesCount = query->getValues().size();
    
    for (auto i = 0; i < valuesCount; ++i) {
        QString valueString{variantValueToString(query->getValues().at(i))};
        
        if (valueString.isEmpty()) 
            return false;
        
        sqlString += (valueString + (i + 1 == valuesCount ? ' ' : ','));
    }
    
    sqlString += ");";
    
    result = std::make_unique<DatabaseQueryParserResultSQL>(sqlString);
    
    return true;
}

bool DatabaseQueryParserStandard::parseUpdateQuery(const DatabaseQueryStandardUpdate * const query,
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    if (!query) return false;
    
    QString sqlString{};
    
    sqlString += "UPDATE ";
    sqlString += query->getTables().front() + " ";
    sqlString += "SET";
    
    auto attributesCount = query->getAttributes().length();
    
    for (auto i = 0; i < attributesCount; ++i) {
        QString valueString{variantValueToString(query->getValues().at(i))};
        
        if (valueString.isEmpty()) 
            return false;
        
        sqlString += (query->getAttributes().at(i) + " = " + valueString + (i + 1 == attributesCount ? ") " : ","));
    }
    
    if (!query->getConditions().empty()) {
        QString conditionsString{conditionsListToString(query->getConditions())};
        
        if (conditionsString.isEmpty()) return false;
        
        sqlString += conditionsString;
    }
    
    sqlString += ';';
    
    result = std::make_unique<DatabaseQueryParserResultSQL>(sqlString);
    
    return true;
}

bool DatabaseQueryParserStandard::parseDeleteQuery(const DatabaseQueryStandardDelete * const query, 
                                                   std::unique_ptr<DatabaseQueryParserResultInterface> &result)
{
    if (!query) return false;
    
    QString sqlString{};
    
    sqlString += "DELETE FROM ";
    sqlString += query->getTables().front() + " ";
    
    if (!query->getConditions().empty()) {
        QString conditionsString{conditionsListToString(query->getConditions())};
        
        if (conditionsString.isEmpty()) return false;
        
        sqlString += conditionsString;
    }
    
    sqlString += ';';
    
    result = std::make_unique<DatabaseQueryParserResultSQL>(sqlString);
    
    return true;
}

QString DatabaseQueryParserStandard::orderFlagToString(const DatabaseQueryContextStandard::OrderFlag orderFlag) const
{
    switch (orderFlag) {
    case DatabaseQueryContextStandard::OrderFlag::OF_ASC:  return "ASC";
    case DatabaseQueryContextStandard::OrderFlag::OF_DESC: return "DESC";
    }
    
    return QString{};
}

QString DatabaseQueryParserStandard::variantValueToString(const QVariant &value) const
{
    if (value.isNull()) return QString{};
    
    switch (value.type()) {
    case QVariant::Type::Char:
    case QVariant::Type::String:   {return (QString{'\''} + value.toString() + '\'');};
    case QVariant::Type::Bool:
    case QVariant::Type::LongLong:
    case QVariant::Type::ULongLong:
    case QVariant::Type::Int:
    case QVariant::Type::UInt:
    case QVariant::Type::Double:   {return value.toString();};
    case QVariant::Type::DateTime: {return QString{'\''} + value.toDateTime().toString(Qt::ISODate) + '\'';};
    case QVariant::Type::Date:     {return QString{'\''} + value.toDate().toString(Qt::ISODate) + '\'';};
    }
    
    return QString{};
}

QString DatabaseQueryParserStandard::conditionsListToString(const DatabaseQueryUsingCondition::ConditionsList &conditions) const
{
    if (conditions.empty()) return QString{};
    
    QString result{"WHERE "};
    
    auto conditionsCount = conditions.size();
    
    for (auto i = 0; i < conditionsCount; ++i) {
        DatabaseQueryConditionStandard *curCondition{dynamic_cast<DatabaseQueryConditionStandard*>(conditions.at(i).get())};
        
        if (!curCondition) return QString{};
        
        QString conditionValueString{curCondition->toString()};
        
        if (conditionValueString.isEmpty()) return QString{};
        
        result += (conditionValueString + (i + 1 == conditionsCount ? " " : " AND "));
    }
    
    return result;
}
