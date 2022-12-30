#ifndef SEPERATEOPERATION_H
#define SEPERATEOPERATION_H

#include "baseoperation.h"
#include<QString>

//拆开合并的端口
class SeperateOperation:public BaseOperation
{
public:
    SeperateOperation(QString compoundPortId);
    virtual ~SeperateOperation();
    virtual void execOperation(ComponentList*);
private:
    QString portToSeperate;
};

#endif // SEPERATEOPERATION_H
