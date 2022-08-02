#ifndef DATABASEQUERYCONTEXTSTANDARD_H
#define DATABASEQUERYCONTEXTSTANDARD_H

#include <stdint.h>
#include <QVariant>
#include <QDate>
#include <QDateTime>

#include "DatabaseContext.h"

namespace DatabaseQueryContextStandard
{

enum DatabaseQueryType : DatabaseContext::DatabaseQueryTypeType {
    DQT_SELECT = DatabaseContext::DatabaseType::DT_INVALID + 1,
    DQT_INSERT,
    DQT_UPDATE,
    DQT_DELETE
};

enum DatabaseQueryConditionType : DatabaseContext::DatabaseQueryConditionTypeType {
    DQCT_GREATER_THEN = DatabaseContext::DatabaseQueryConditionType::DQCT_INVALID + 1,
    DQCT_LESS_THEN,
    DQCT_EQUAL_TO,
    DQCT_LIKE
};

enum OrderFlag : uint8_t {
    OF_NO_ORDER = 0,
    OF_ASC,
    OF_DESC
};

inline QString variantValueToString(const QVariant &value)
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

};

#endif // DATABASEQUERYCONTEXTSTANDARD_H
