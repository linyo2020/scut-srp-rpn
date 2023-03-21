#ifndef ADDANDMERGEOPERATION_H
#define ADDANDMERGEOPERATION_H

#include "baseoperation.h"
class AddAndMergeOperation:public BaseOperation
{
public:
    //传入组件的名称，创建一个新的组件实例，同时合并一系列端口，可以通过`NEW_COMPONENT_ID`指定新创建组件的端口，用法与`ReplaceWithNewOperation`相同。
    AddAndMergeOperation(const QString &componentName,const QList<QPair<QString,QString> >&mergePortList);
    AddAndMergeOperation(const AddAndMergeOperation&)=delete;
    AddAndMergeOperation & operator=(const AddAndMergeOperation&)=delete;
    virtual ~AddAndMergeOperation()=default;
    virtual void execOperation(ComponentList*) const override;
    virtual AddAndMergeOperation* clone()const override;
    virtual OperationType getType()const override{return type;}
    virtual QList<QString*> getArguments() override;
    virtual QList<QPair<QString,QString> > *getMergeList() override;

    virtual OPERATION_ATTR toXML() const override;
private:
    constexpr static OperationType type=ADD_AND_MERGE_OPERATION;
    QString newComponentName;
    QList<QPair<QString,QString> >mergePortList;
};

#endif // ADDANDMERGEOPERATION_H
