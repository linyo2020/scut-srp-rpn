#include "timerule.h"

TimeRule::TimeRule(QString name,QString comment,QList<QList<CONDITION> >conditionList,QList<BaseOperation*>operationList)
    :BaseRule(name,comment,conditionList,operationList)
{

}

TimeRule::~TimeRule()
{

}

bool TimeRule::isSatisfy(ComponentList* componentList)
{
    bool computeResult=false;
    for(QList<CONDITION>orCompute:conditionList)
    {
        bool andComputeResult=true;
        for(CONDITION andCompute:orCompute)
        {
            switch (andCompute.conditionOption) {
            case REACH_TIME_POINT:
                switch (andCompute.symbol) {
                case EQUAL:
                    if(andCompute.value.toDouble()!=totalSimuTime)
                        andComputeResult&=false;
                    break;
                case NOT_EQUAL:
                    if(andCompute.value.toDouble()==totalSimuTime)
                        andComputeResult&=false;
                    break;
                case GREATER:
                    if(andCompute.value.toDouble()<=totalSimuTime)
                        andComputeResult&=false;
                    break;
                case LESS:
                    if(andCompute.value.toDouble()>=totalSimuTime)
                        andComputeResult&=false;
                    break;
                case GREATER_EQUAL:
                    if(andCompute.value.toDouble()<totalSimuTime)
                        andComputeResult&=false;
                    break;
                case LESS_EQUAL:
                    if(andCompute.value.toDouble()>totalSimuTime)
                        andComputeResult&=false;
                    break;
                default:
                    andComputeResult&=false;
                    break;
                }
                break;
            case FIRE_REACH_TIME_DURATION:
                //TODO:如何监视使能时间尚不清楚
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
    totalSimuTime+=step;

    for(BaseOperation* eachOperation:operationList)
        eachOperation->execOperation(componentList);

    return computeResult;
}

void TimeRule::simulationInit(RULE_INITIALIZE_INFOMATION initInfo)
{
    step=initInfo.step;
    totalSimuTime=0.0;
}

