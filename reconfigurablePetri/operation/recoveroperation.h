#ifndef RECOVEROPERATION_H
#define RECOVEROPERATION_H

#include "baseoperation.h"

class RecoverOperation:public BaseOperation
{
public:
    RecoverOperation(const QString& componentId);//传入实例id,往网中恢复实例，不合并任何端口，传入已有组件实例id的add操作
    RecoverOperation(const RecoverOperation&)=delete;
    RecoverOperation& operator=(const RecoverOperation&)=delete;
    virtual ~RecoverOperation();
    virtual void execOperation(ComponentList*) const override;
    virtual RecoverOperation* clone() const override;
    virtual OperationType getType()const override{return type;}
    virtual QList<QString*> getArguments() override;

    virtual OPERATION_ATTR toXML() const override;
private:
    QString componentInstanceId;
    constexpr static OperationType type=RECOVER_OPERATION;
};

#endif // RECOVEROPERATION_H
