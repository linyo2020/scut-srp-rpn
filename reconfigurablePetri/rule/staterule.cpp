#include"staterule.h"
#include"place.h"

StateRule::StateRule(QString name, QString comment, QList<QList<CONDITION> > conditionList, QList<BaseOperation *> operationList)
    :BaseRule (name,comment,conditionList,operationList)
{

}

StateRule::~StateRule()
{

}

bool StateRule::isSatisfy(ComponentList* componentList)
{
    bool computeResult=false;
    for(QList<CONDITION>orCompute:conditionList)
    {
        bool andComputeResult=true;
        for(CONDITION andCompute:orCompute)
        {
            switch (andCompute.conditionOption) {
            case TOKEN_COMPARE:
            {
                Place* p=componentList->getCertainPlace(andCompute.monitorFactor);
                if(p==nullptr)
                {
                    andComputeResult&=false;
                    break;
                }
                if(false==doubleCompare(p->getTokens(),
                                        andCompute.value.toDouble(),
                                        andCompute.symbol))//不满足条件则置false，满足条件不做处理
                    andComputeResult&=false;
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
    //执行操作
    if(computeResult)
    {
        for(BaseOperation* eachOperation:operationList)
        eachOperation->execOperation(componentList);
    }
    return computeResult;
}

void StateRule::simulationInit(RULE_INITIALIZE_INFOMATION initInfo)
{

}
