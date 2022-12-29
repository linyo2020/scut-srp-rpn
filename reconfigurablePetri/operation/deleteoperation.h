#ifndef DELETEOPERATION_H
#define DELETEOPERATION_H

#include "baseoperation.h"
#include<QString>

//删除一个组件实例
class DeleteOperation:public BaseOperation
{
public:
    DeleteOperation(QString componentId);
    virtual ~DeleteOperation();
    virtual void execOperation(ComponentList*);
private:
    QString ComponentInstanceToDelete;
};

#endif // DELETEOPERATION_H
