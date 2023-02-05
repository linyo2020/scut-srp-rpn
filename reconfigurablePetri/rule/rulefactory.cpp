#include "rulefactory.h"
#include "baserule.h"
#include "eventrule.h"
#include "staterule.h"
#include "timerule.h"
#include "../defs.h"
#include "operation/operationfactory.h"
#include "operation/baseoperation.h"


BaseRule *RuleFactory::fromXML(const RULE_ATTR &rule)
{
    if(rule.type<=0||rule.type>MAX_RULE_TYPE)
        return nullptr;

    QList<BaseOperation*> operationList;
    for(const auto &operation:rule.operations)
    {
        BaseOperation *o=OperationFactory::fromXML(operation);
        if(nullptr==o)
            continue;
        operationList.push_back(o);
    }

    RuleType type=RuleType(rule.type);
    switch (type) {
    case EVENT_RULE:
        return new EventRule(rule.name,rule.comment,rule.conditions,operationList);
    case STATE_RULE:
        return new StateRule(rule.name,rule.comment,rule.conditions,operationList);
    case TIME_RULE:
        return new TimeRule(rule.name,rule.comment,rule.conditions,operationList);
    default:
        return nullptr;
    }
}
