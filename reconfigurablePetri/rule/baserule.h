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
    BaseRule(const QString& name,const QString& comment,const QList<QList<CONDITION> >& conditionList,const QList<BaseOperation* >&operationList);
    BaseRule(const BaseRule&)=delete;
    BaseRule& operator=(const BaseRule&)=delete;
    virtual ~BaseRule();
    virtual bool isSatisfy(ComponentList*,const RULE_RUNTIME_INFOMATION&)=0;
    virtual void initRule()=0;
    virtual BaseRule* clone() const=0;//拷贝并返回类指针，建议用基类指针接收
    virtual RuleType getType()const{return type;}

    QString getName()const{return name;}
    void setName(const QString &n){name=n;}
    QString getComment()const{return comment;}
    void setComment(const QString &c){comment=c;}
    QList<QList<CONDITION> > &getConditionList(){return conditionList;}
    QList<BaseOperation* > &getOperationList(){return operationList;}


private:
    constexpr static RuleType type=BASE_RULE;

protected:  
    QString name,comment;
    QList<QList<CONDITION> >conditionList;
    QList<BaseOperation* >operationList;

    //浮点数比较
private:
    constexpr static double EPSINON=1e-8;
    inline bool doubleEqual(double,double);
    inline bool doubleNotEqual(double,double);
    inline bool doubleGreater(double,double);
    inline bool doubleLess(double,double);
    inline bool doubleGreaterEqual(double,double);
    inline bool doubleLessEqual(double,double);

protected:
    bool doubleCompare(double,double,ComparisonSymbol);
};


#endif//BASERULE_H
