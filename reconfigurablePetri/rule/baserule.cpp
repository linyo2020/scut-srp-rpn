#include "rule/baserule.h"
#include<QString>
BaseRule::BaseRule(QString name,QString comment,QList<QList<CONDITION> >conditionList,QList<BaseOperation*>operationList)
    :name(name),comment(comment),conditionList(conditionList),operationList(operationList)
{
}

BaseRule::~BaseRule()
{
}

