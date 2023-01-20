#ifndef STATERULE_H
#define STATERULE_H

#include "baserule.h"

class StateRule:public BaseRule
{
public:
    StateRule(QString name,QString comment,QList<QList<CONDITION> >conditionList,QList<BaseOperation*>operationList);
    virtual ~StateRule();
    virtual bool isSatisfy(ComponentList*);
    virtual void simulationInit(RULE_INITIALIZE_INFOMATION initInfo);
};
#endif // STATERULE_H
