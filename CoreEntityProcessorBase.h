#ifndef COREENTITYPROCESSORBASE_H
#define COREENTITYPROCESSORBASE_H

#include <QJsonObject>
#include <QJsonValue>

#include "CoreContext.h"

#include "EntityGrade.h"
#include "EntityQuote.h"
#include "EntitySession.h"
#include "EntityUser.h"

class CoreEntityProcessorBase
{
public:
    CoreEntityProcessorBase         () = default;
    virtual ~CoreEntityProcessorBase() = default;
    
    bool entityToJSON(const EntityBase*const entity,
                      QJsonObject &jsonObject);
    bool jsonToEntity(const CoreContext::EntityType entityType,
                      const QJsonObject &jsonObject,
                      std::unique_ptr<EntityBase> &entity);
    
protected:
    virtual bool gradeToJSON(const EntityGrade*const grade,
                             QJsonObject &jsonObject);
    virtual bool quoteToJSON(const EntityQuote*const quote,
                             QJsonObject &jsonObject);
    virtual bool sessionToJSON(const EntitySession*const session,
                               QJsonObject &jsonObject);
    virtual bool userToJSON(const EntityUser*const user,
                            QJsonObject &jsonObject);
    
    virtual bool jsonToGrade(const QJsonObject &jsonObject,
                             std::unique_ptr<EntityBase> &grade);
    virtual bool jsonToQuote(const QJsonObject &jsonObject,
                             std::unique_ptr<EntityBase> &quote);
//    virtual bool jsonToSession(const QJsonObject &jsonObject,
//                               std::unique_ptr<EntityBase> &session);
    virtual bool jsonToUser(const QJsonObject &jsonObject,
                            std::unique_ptr<EntityBase> &user);
};

#endif // COREENTITYPROCESSORBASE_H
