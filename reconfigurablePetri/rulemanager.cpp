#include"rulemanager.h"
RuleManager::RuleManager()
    :m_componentList(nullptr)
{

}

void RuleManager::addRule(BaseRule* rule)
{
    ruleList.append(rule);
}

bool RuleManager::deleteRule(int index)
{
    if(index<0 && index>=ruleList.size())
        return false;
    ruleList.removeAt(index);
    return true;
}

QList<BaseRule*> RuleManager::getRuleList()
{
    return ruleList;
}

bool RuleManager::applyRule()
{
    if(m_componentList==nullptr)
        return false;
    bool isReconfig=false;
    for(BaseRule* eachRule:ruleList)
    {
        if(true==eachRule->isSatisfy(m_componentList))
            isReconfig=true;
    }
    return isReconfig;
}

void RuleManager::initRule(ComponentList*componentList,RULE_INITIALIZE_INFOMATION initInfo)
{
    m_componentList=componentList;
    for(BaseRule* eachRule:ruleList)
        eachRule->simulationInit(initInfo);
}
