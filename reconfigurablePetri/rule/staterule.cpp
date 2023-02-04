#include"staterule.h"
#include"place.h"

StateRule::StateRule(const QString& name, const QString& comment, const QList<QList<CONDITION> >& conditionList, const QList<BaseOperation *>& operationList)
    :BaseRule (name,comment,conditionList,operationList)
{

}

StateRule::~StateRule()
{

}

bool StateRule::isSatisfy(ComponentList* componentList,const RULE_RUNTIME_INFOMATION& runtimeInfo)
{
    if(conditionList.empty()||operationList.empty())
        return false;
    bool computeResult=false;
    for(const QList<CONDITION>& orCompute:conditionList)
    {
        bool andComputeResult=true;
        for(const CONDITION& andCompute:orCompute)
        {
            switch (andCompute.conditionOption) {
            case TOKEN_COMPARE:
            {
                double token=componentList->getCertainPlaceToken(andCompute.monitorFactor);
                if(doubleCompare(-1.0,token,EQUAL))
                {
                    andComputeResult&=false;
                    break;
                }
                if(false==doubleCompare(token,
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

void StateRule::initRule()
{

}

StateRule *StateRule::clone() const
{
    QList<QList<CONDITION> > newConditionListQList;
    QList<BaseOperation*> newOperationList;
    int currentRow=0;
    for(const auto& andCondition:conditionList)
    {
        newConditionListQList.push_back(QList<CONDITION>());
        for(const auto& orCondition:andCondition)
        {
            newConditionListQList[currentRow].push_back(CONDITION(orCondition));
        }
        currentRow++;
    }
    for(const auto operation:operationList)
        newOperationList.push_back(operation->clone());
    return new StateRule(name,comment,newConditionListQList,newOperationList);
}
