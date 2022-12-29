#ifndef RECOVEROPERATION_H
#define RECOVEROPERATION_H

#include "baseoperation.h"

class RecoverOperation:public BaseOperation
{
public:
    RecoverOperation(QString componentId);//传入实例id,往网中恢复实例，不合并任何端口，传入已有组件实例id的add操作
    virtual ~RecoverOperation();
    virtual void execOperation(ComponentList*);
private:
    QString componentInstanceId;
};

#endif // RECOVEROPERATION_H
