#include "rule/baserule.h"
#include<QString>
BaseRule::BaseRule(const QString& name,const QString& comment,const QList<QList<CONDITION> >&conditionList,const QList<BaseOperation* >&operationList)
    :name(name),comment(comment),conditionList(conditionList),operationList(operationList)
{

}

BaseRule::~BaseRule()
{
    for(auto operation:operationList)
        delete operation;
}

bool BaseRule::doubleEqual(double a, double b)
{
    return (a+EPSINON>b&&a-EPSINON<b)?true:false;
}

bool BaseRule::doubleNotEqual(double a, double b)
{
    return (a+EPSINON>b&&a-EPSINON<b)?false:true;
}

bool BaseRule::doubleGreater(double a, double b)
{
    return (a>b+EPSINON)?true:false;
}

bool BaseRule::doubleLess(double a, double b)
{
    return (a<b-EPSINON)?true:false;
}

bool BaseRule::doubleGreaterEqual(double a, double b)
{
    return (doubleGreater(a,b)||doubleEqual(a,b))?true:false;
}

bool BaseRule::doubleLessEqual(double a, double b)
{
    return (doubleLess(a,b)||doubleEqual(a,b))?true:false;
}

bool BaseRule::doubleCompare(double a, double b, ComparisonSymbol symbol)
{
    switch (symbol) {
    case EQUAL:
        return doubleEqual(a,b);
    case NOT_EQUAL:
        return doubleNotEqual(a,b);
    case GREATER:
        return doubleGreater(a,b);
    case LESS:
        return doubleLess(a,b);
    case GREATER_EQUAL:
        return doubleGreaterEqual(a,b);
    case LESS_EQUAL:
        return doubleLessEqual(a,b);
    default:
        return false;
    }
}

