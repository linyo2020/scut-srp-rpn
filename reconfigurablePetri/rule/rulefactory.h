#ifndef RULEFACTORY_H
#define RULEFACTORY_H

struct RULE_ATTR;

class BaseRule;
class EventRule;
class StateRule;
class TimeRule;

class RuleFactory
{
public:
    explicit RuleFactory()=delete;
    static BaseRule *fromXML(const RULE_ATTR &rule);
};

#endif // RULEFACTORY_H
