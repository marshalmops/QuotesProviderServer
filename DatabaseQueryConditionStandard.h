#ifndef DATABASEQUERYCONDITIONSTANDARD_H
#define DATABASEQUERYCONDITIONSTANDARD_H

#include <QString>
#include <QVariant>

#include "DatabaseQueryConditionBase.h"

#include "DatabaseQueryContextStandard.h"

class DatabaseQueryConditionStandard : public DatabaseQueryConditionBase
{
public:
    DatabaseQueryConditionStandard(const DatabaseContext::DatabaseQueryConditionTypeType type = DatabaseContext::DatabaseQueryConditionType::DQCT_INVALID,
                                   const QString &attributeName = QString{},
                                   const QVariant &value = QVariant{});
    
    const QString&  getAttributeName() const;
    const QVariant& getValue        () const;
    
    QString toString() const;
    
    virtual bool isValid() const override;
    
protected:
    QString  m_attributeName;
    QVariant m_value;
};

#endif // DATABASEQUERYCONDITIONSTANDARD_H
