#ifndef ADDOPERATION_H
#define ADDOPERATION_H

#include "baseoperation.h"

class AddOperation:public BaseOperation
{
public:
    AddOperation(QString componentName);//传入组件的名称，创建一个新的组件实例，编号自动分配。要传入已有实例id以进行增加组件操作，使用RecoverOperation。
    virtual ~AddOperation();
    virtual void execOperation(ComponentList*);
private:
    QString newComponentName;
};

#endif // ADDOPERATION_H
