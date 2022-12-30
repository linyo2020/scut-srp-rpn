#ifndef TIMERULE_H
#define TIMERULE_H

#include "baserule.h"

class TimeRule : public BaseRule
{
public:
    TimeRule(QString name,QString comment,QList<QList<CONDITION> >conditionList,QList<BaseOperation*>operationList);
    virtual ~TimeRule();
    virtual bool isSatisfy(ComponentList*);
    virtual void simulationInit(RULE_INITIALIZE_INFOMATION initInfo);
private:
    double step,totalSimuTime;
};

#endif // TIMERULE_H
