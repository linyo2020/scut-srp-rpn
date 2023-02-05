#ifndef EVENTRULE_H
#define EVENTRULE_H

#include "baserule.h"

class EventRule:public BaseRule
{
public:
    EventRule(const QString& name,const QString& comment,const QList<QList<CONDITION> >& conditionList,const QList<BaseOperation*>& operationList);
    EventRule(const EventRule&)=delete;
    EventRule& operator=(const EventRule&)=delete;
    virtual ~EventRule();
    virtual bool isSatisfy(ComponentList*,const RULE_RUNTIME_INFOMATION&)override;
    virtual void initRule()override;
    virtual EventRule *clone() const override;
    virtual RuleType getType()const override{return type;}

    virtual RULE_ATTR toXML() const override;
private:
    constexpr static RuleType type=EVENT_RULE;
};

#endif // EVENTRULE_H
