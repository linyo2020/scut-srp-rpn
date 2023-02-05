#include "timerule.h"
#include "place.h"

TimeRule::TimeRule(const QString &name, const QString &comment, const QList<QList<CONDITION> > &conditionList, const QList<BaseOperation *> &operationList)
    :BaseRule(name,comment,conditionList,operationList),step(0.0),totalSimuTime(0.0),durationCounter(0.0)
{

}

TimeRule::~TimeRule()
{

}

bool TimeRule::isSatisfy(ComponentList* componentList,const RULE_RUNTIME_INFOMATION& runtimeInfo)
{
    if(conditionList.empty()||operationList.empty())
        return false;
    step=runtimeInfo.totalTime-totalSimuTime;
    totalSimuTime=runtimeInfo.totalTime;
    bool computeResult=false;
    for(const QList<CONDITION>&orCompute:conditionList)
    {
        bool andComputeResult=true;
        for(const CONDITION& andCompute:orCompute)
        {
            switch (andCompute.conditionOption) {
            case TIME_POINT_COMPARE://当前总仿真时间和某个时间点比较
                if(false==doubleCompare(andCompute.value.toDouble(),totalSimuTime,andCompute.symbol))//不满足条件则置false，满足条件不做处理
                    andComputeResult&=false;
                break;
            case CERTAIN_TOKEN_DURATION://对token的比较满足，并维持一定的时间。
            {
                static bool isLastStepFrontPartSatisfy=false;
                double token=componentList->getCertainPlaceToken(andCompute.monitorFactor);
                if(doubleCompare(-1.0,token,EQUAL))
                {
                    andComputeResult&=false;
                    break;
                }
                if(false==doubleCompare(token,
                                        andCompute.value.toDouble(),
                                        andCompute.symbol))
                {
                    andComputeResult&=false;
                    durationCounter=0.0;
                    isLastStepFrontPartSatisfy=false;
                }
                else
                {
                    if(andCompute.rearPart==nullptr)//后部为空
                    {
                        andComputeResult&=false;
                        break;
                    }
                    if(!isLastStepFrontPartSatisfy)
                        isLastStepFrontPartSatisfy=true;
                    else
                        durationCounter+=step;
                    if(false==doubleCompare(durationCounter,
                                            andCompute.rearPart->value.toDouble(),
                                            andCompute.rearPart->symbol))//对持续的时长比较
                        andComputeResult&=false;
                }
            }
                break;
            case TIME_TO_REACH_CERTAIN_TOKEN://令token满足比较,所需的时间
            {
                double token=componentList->getCertainPlaceToken(andCompute.monitorFactor);
                if(doubleCompare(-1.0,token,EQUAL))
                {
                    andComputeResult&=false;
                    durationCounter=0.0;
                    break;
                }
                durationCounter+=step;
                if(false==doubleCompare(token,
                                        andCompute.value.toDouble(),
                                        andCompute.symbol))
                    andComputeResult&=false;
                else
                {
                    if(andCompute.rearPart==nullptr)
                    {
                        andComputeResult&=false;
                        break;
                    }
                    if(false==doubleCompare(durationCounter,
                                            andCompute.rearPart->value.toDouble(),
                                            andCompute.rearPart->symbol))//监测是否违反对达到目标token的时长要求
                        andComputeResult&=false;
                }
            }
                break;
            case FIRE_REACH_TIME_DURATION:
                //TODO:次要需求
                break;
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

void TimeRule::initRule()
{
    step=0.0;
    totalSimuTime=0.0;
    durationCounter=0.0;
}

TimeRule *TimeRule::clone() const
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
    return new TimeRule(name,comment,newConditionListQList,newOperationList);
}

RULE_ATTR TimeRule::toXML() const
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

