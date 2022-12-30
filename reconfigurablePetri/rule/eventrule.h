#ifndef EVENTRULE_H
#define EVENTRULE_H

#include "baserule.h"

class EventRule:public BaseRule
{
public:
    EventRule(QString name,QString comment,QList<QList<CONDITION> >conditionList,QList<BaseOperation*>operationList);
    virtual ~EventRule();
    virtual bool isSatisfy(ComponentList*);
    virtual void simulationInit(RULE_INITIALIZE_INFOMATION initInfo);
};

#endif // EVENTRULE_H
