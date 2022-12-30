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
            case TOKEN_COMPARE:
                switch (andCompute.symbol) {
                case EQUAL:
                    if(componentList->getCertainPlace(andCompute.monitorFactor)->getTokens()!=andCompute.value.toDouble())
                        andComputeResult&=false;
                    break;
                case NOT_EQUAL:
                    if(componentList->getCertainPlace(andCompute.monitorFactor)->getTokens()==andCompute.value.toDouble())
                        andComputeResult&=false;
                    break;
                case GREATER:
                    if(componentList->getCertainPlace(andCompute.monitorFactor)->getTokens()<=andCompute.value.toDouble())
                        andComputeResult&=false;
                    break;
                case LESS:
                    if(componentList->getCertainPlace(andCompute.monitorFactor)->getTokens()>=andCompute.value.toDouble())
                        andComputeResult&=false;
                    break;
                case GREATER_EQUAL:
                    if(componentList->getCertainPlace(andCompute.monitorFactor)->getTokens()<andCompute.value.toDouble())
                        andComputeResult&=false;
                    break;
                case LESS_EQUAL:
                    if(componentList->getCertainPlace(andCompute.monitorFactor)->getTokens()>andCompute.value.toDouble())
                        andComputeResult&=false;
                    break;
                default:
                    andComputeResult&=false;
                    break;
                }
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

    for(BaseOperation* eachOperation:operationList)
        eachOperation->execOperation(componentList);

    return computeResult;
}

void EventRule::simulationInit(RULE_INITIALIZE_INFOMATION initInfo)
{

}
