#ifndef DELETEOPERATION_H
#define DELETEOPERATION_H

#include "baseoperation.h"
#include<QString>

//删除一个组件实例
class DeleteOperation:public BaseOperation
{
public:
    DeleteOperation(const QString& componentId);
    DeleteOperation(const DeleteOperation&)=delete;
    DeleteOperation& operator=(const DeleteOperation&)=delete;
    virtual ~DeleteOperation()=default;
    virtual void execOperation(ComponentList*) const override;
    virtual DeleteOperation* clone() const override;
    virtual OperationType getType()const override{return type;}
    virtual QList<QString*> getArguments() override;

    OPERATION_ATTR toXML() const override;
private:
    QString ComponentInstanceToDelete;
    constexpr static OperationType type=DELETE_OPERATION;
};

#endif // DELETEOPERATION_H
