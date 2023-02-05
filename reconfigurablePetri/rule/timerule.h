#ifndef TIMERULE_H
#define TIMERULE_H

#include "baserule.h"

class TimeRule : public BaseRule
{
public:
    TimeRule(const QString& name,const QString& comment,const QList<QList<CONDITION> >&conditionList,const QList<BaseOperation*>&operationList);
    TimeRule(const TimeRule&)=delete;
    TimeRule& operator=(const TimeRule&)=delete;
    virtual ~TimeRule();
    virtual bool isSatisfy(ComponentList*,const RULE_RUNTIME_INFOMATION&)override;
    virtual void initRule()override;
    virtual TimeRule *clone() const override;
    virtual RuleType getType()const override{return type;}

    virtual RULE_ATTR toXML() const override;
private:
    double step,totalSimuTime,durationCounter;//step:距离上次验证规则经过的步长；durationCounter：某种条件下的持续时间
    constexpr static RuleType type=TIME_RULE;
};

#endif // TIMERULE_H
