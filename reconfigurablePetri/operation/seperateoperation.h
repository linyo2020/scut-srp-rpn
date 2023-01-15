#ifndef SEPERATEOPERATION_H
#define SEPERATEOPERATION_H

#include "baseoperation.h"
#include<QString>

//拆开合并的端口
class SeperateOperation:public BaseOperation
{
public:
    SeperateOperation(QString compoundPortId_1,QString compoundPortId_2);
    virtual ~SeperateOperation();
    virtual void execOperation(ComponentList*);
private:
    QString portToSeperate_1,portToSeperate_2;
};

#endif // SEPERATEOPERATION_H
