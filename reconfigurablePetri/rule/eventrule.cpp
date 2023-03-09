#include "eventrule.h"


EventRule::EventRule(const QString& name, const QString& comment, const QList<QList<CONDITION> >& conditionList, const QList<BaseOperation *>& operationList)
    :BaseRule (name,comment,conditionList,operationList)
{

}

bool EventRule::isSatisfy(ComponentList* componentList,const RULE_RUNTIME_INFOMATION& runtimeInfo)
{
    Q_UNUSED(runtimeInfo);

    if(conditionList.empty()||operationList.empty())
        return false;
    bool computeResult=false;
    for(const QList<CONDITION>&orCompute:conditionList)
    {
        bool andComputeResult=true;
        for(const CONDITION& andCompute:orCompute)
        {
            switch (andCompute.conditionOption) {
            default:
                andComputeResult&=false;
                break;
            }
            if(false==andComputeResult)
                break;
        }
        computeResult|=andComputeResult;
        if(true==computeResult)
            break;
    }
    //执行操作
    if(computeResult)
    {
        for(BaseOperation* eachOperation:operationList)
            eachOperation->execOperation(componentList);
    }
    return computeResult;
}

void EventRule::initRule()
{

}

EventRule *EventRule::clone() const
{
    QList<QList<CONDITION> > newConditionListQList;
    QList<BaseOperation*> newOperationList;
    for(const auto& orCondition:conditionList)
    {
        newConditionListQList.push_back(QList<CONDITION>());
        for(const auto& andCondition:orCondition)
        {
            newConditionListQList.last().push_back(CONDITION(andCondition));
        }
    }
    for(const auto operation:operationList)
        newOperationList.push_back(operation->clone());
    return new EventRule(name,comment,newConditionListQList,newOperationList);
}

RULE_ATTR EventRule::toXML() const
{
    RULE_ATTR rule;
    rule.name=name;
    rule.comment=comment;
    rule.type=type;
    for(const auto &orCondition:conditionList)
    {
        rule.conditions.push_back(QList<CONDITION>());
        for(const auto &andCondition:orCondition)
        {
            rule.conditions.last().push_back(CONDITION(andCondition));
        }
    }
    for(const auto operation:operationList)
        rule.operations.push_back(operation->toXML());
    return rule;
}
