#pragma once
#ifndef BASERULE_H
#define BASERULE_H

#include "operation/baseoperation.h"
#include "../componentlist.h"
#include<QVariant>
#include<QString>
#include "../defs.h"

class BaseRule
{
public:
    //conditionList:内层QList为与运算，外层QList为或运算
    //例：{{CONDITION1,CONDITION2},{CONDITION3,CONDITION4,CONDITION5}}相当于逻辑运算：(CONDITION1&&CONDITION2)||(CONDITION3&&CONDITION4&&CONDITION5)
    BaseRule(QString name,QString comment,QList<QList<CONDITION> > conditionList,QList<BaseOperation*>operationList);
    virtual ~BaseRule();
    virtual bool isSatisfy(ComponentList*)=0;
    virtual void simulationInit(RULE_INITIALIZE_INFOMATION initInfo)=0;



protected:  
    QString name,comment;
    QList<QList<CONDITION> >conditionList;
    QList<BaseOperation*>operationList;

    //浮点数比较
private:
    constexpr static double EPSINON=1e-8;
    bool doubleEqual(double,double);
    bool doubleNotEqual(double,double);
    bool doubleGreater(double,double);
    bool doubleLess(double,double);
    bool doubleGreaterEqual(double,double);
    bool doubleLessEqual(double,double);

protected:
    bool doubleCompare(double,double,ComparisonSymbol);
};


#endif//BASERULE_H
