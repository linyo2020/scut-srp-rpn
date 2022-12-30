#ifndef MERGEOPERATION_H
#define MERGEOPERATION_H

#include "baseoperation.h"

//合并端口
class MergeOperation:public BaseOperation
{
public:
    MergeOperation(QString portId_1,QString portId_2);
    virtual ~MergeOperation();
    virtual void execOperation(ComponentList*);
private:
    QString portId1,portId2;
};

#endif // MERGEOPERATION_H
