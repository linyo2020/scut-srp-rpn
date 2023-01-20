#include "eventrule.h"


EventRule::EventRule(QString name, QString comment, QList<QList<CONDITION> > conditionList, QList<BaseOperation *> operationList)
    :BaseRule (name,comment,conditionList,operationList)
{

}

EventRule::~EventRule()
{

}

bool EventRule::isSatisfy(ComponentList* componentList)
{
    bool computeResult=false;
    for(QList<CONDITION>orCompute:conditionList)
    {
        bool andComputeResult=true;
        for(CONDITION andCompute:orCompute)
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

void EventRule::simulationInit(RULE_INITIALIZE_INFOMATION initInfo)
{

}
