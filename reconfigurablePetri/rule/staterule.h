#ifndef STATERULE_H
#define STATERULE_H

#include "baserule.h"

class StateRule:public BaseRule
{
public:
    StateRule(const QString& name,const QString& comment,const QList<QList<CONDITION> >& conditionList,const QList<BaseOperation*>& operationList);
    StateRule(const StateRule&)=delete;
    StateRule& operator=(const StateRule&)=delete;
    virtual ~StateRule();
    virtual bool isSatisfy(ComponentList*,const RULE_RUNTIME_INFOMATION&)override;
    virtual void initRule()override;
    virtual StateRule* clone() const override;
};
#endif // STATERULE_H
