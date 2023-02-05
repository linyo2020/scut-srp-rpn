#ifndef SEPERATEOPERATION_H
#define SEPERATEOPERATION_H

#include "baseoperation.h"
#include<QString>

//拆开合并的端口
class SeperateOperation:public BaseOperation
{
public:
    SeperateOperation(const QString& compoundPortId_1,const QString& compoundPortId_2);
    SeperateOperation(const SeperateOperation&)=delete;
    SeperateOperation& operator=(const SeperateOperation&)=delete;
    virtual ~SeperateOperation();
    virtual void execOperation(ComponentList*) const override;
    virtual SeperateOperation *clone() const override;
    virtual OperationType getType()const override{return type;}
    virtual QList<QString*> getArguments() override;

    virtual OPERATION_ATTR toXML() const override;
private:
    QString portToSeperate_1,portToSeperate_2;
    constexpr static OperationType type=SEPERATE_OPERATION;
};

#endif // SEPERATEOPERATION_H
