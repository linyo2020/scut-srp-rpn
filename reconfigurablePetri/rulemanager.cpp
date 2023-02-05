#include"rulemanager.h"
#include"rule/rulefactory.h"
RuleManager::RuleManager()
    :m_componentList(nullptr)
{

}

RuleManager::RuleManager(const RuleManager &other)
{
    for(const auto& eachRule:other.ruleList)
        ruleList.push_back(eachRule->clone());
    m_componentList=other.m_componentList;//仅持有指针，不管理对象内存
}

RuleManager &RuleManager::operator=(const RuleManager &other)
{
    ruleList.clear();
    for(const auto& eachRule:other.ruleList)
        ruleList.push_back(eachRule->clone());
    m_componentList=other.m_componentList;//仅持有指针，不管理对象内存
    return *this;
}

RuleManager::RuleManager(RuleManager &&other)
{
    ruleList=std::forward<QList<BaseRule*>&&>(other.ruleList);
    m_componentList=other.m_componentList;
    other.m_componentList=nullptr;
}

RuleManager &RuleManager::operator=(RuleManager &&other)
{
    ruleList=std::forward<QList<BaseRule*>&&>(other.ruleList);
    m_componentList=other.m_componentList;
    other.m_componentList=nullptr;
    return *this;
}

RuleManager::~RuleManager()
{
    m_componentList=nullptr;
    for(auto eachRule:ruleList)
        delete eachRule;
}

RuleManager::RuleManager(const QList<RULE_ATTR> &rules)
    :m_componentList(nullptr)
{
    for(const auto &rule : rules)
    {
        BaseRule *r=RuleFactory::fromXML(rule);
        if(nullptr==r)
            continue;
        ruleList.push_back(r);
    }
}

QList<RULE_ATTR> RuleManager::toXML() const
{
    QList<RULE_ATTR>rules;
    for(const auto rule:ruleList)
        rules.push_back(rule->toXML());
    return rules;
}

void RuleManager::appendRule(BaseRule* rule)
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

bool RuleManager::swapRule(int a, int b)
{
    if(!(a>=0&&b>=0&&a<ruleList.size()&&b<ruleList.size()))
        return false;
    ruleList.swap(a,b);
    return true;
}

bool RuleManager::moveRule(int from, int to)
{
    if(!(from>=0&&to>=0&&from<ruleList.size()&&to<ruleList.size()))
        return false;
    ruleList.move(from,to);
    return true;
}

const QList<BaseRule *> *RuleManager::getRuleList()  const
{
    return &ruleList;
}

bool RuleManager::replaceRule(int index, BaseRule *newRule)
{
    if(nullptr==newRule)
        return false;
    if(index>=ruleList.size()||index<0)
    {
        delete newRule;
        return false;
    }
    delete ruleList[index];
    ruleList.replace(index,newRule);
    return true;
}

bool RuleManager::applyRule(const RULE_RUNTIME_INFOMATION &runtimeInfo) const
{
    if(m_componentList==nullptr)
        return false;
    bool isReconfig=false;
    for(BaseRule* eachRule:ruleList)
    {
        if(true==eachRule->isSatisfy(m_componentList,runtimeInfo))
            isReconfig=true;
    }
    return isReconfig;
}

void RuleManager::initRule(ComponentList*componentList)
{
    m_componentList=componentList;
    for(auto eachRule:ruleList)
        eachRule->initRule();
}
