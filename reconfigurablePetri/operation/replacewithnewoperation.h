#ifndef REPLACEWITHNEWOPERATION_H
#define REPLACEWITHNEWOPERATION_H

#include "baseoperation.h"
#include<QPair>

class ReplaceWithNewOperation:public BaseOperation
{
public:
    /**
     * @brief 使用自动分配编号的新实例来替换要删除的旧组件实例，并可选择合并一系列端口
     * @param componentIdToReplace 要删除的组件实例id
     * @param componentNameToAdd 要新增的组件名称
     * @param mergePortList 一系列要合并的端口，使用NEW_COMPONENT_ID来指代新增组件的id，例：NEW_COMPONENT_ID+"&"+placeName
     */
    ReplaceWithNewOperation(const QString& componentIdToReplace,const QString& componentNameToAdd,const QList<QPair<QString,QString> >& mergePortList);
    ReplaceWithNewOperation(const ReplaceWithNewOperation&)=delete;
    ReplaceWithNewOperation& operator=(const ReplaceWithNewOperation&)=delete;
    virtual ~ReplaceWithNewOperation()=default;
    virtual void execOperation(ComponentList*) const override;
    virtual ReplaceWithNewOperation *clone() const override;
    virtual OperationType getType()const override{return type;}
    virtual QList<QString*> getArguments() override;
    virtual QList<QPair<QString,QString> > *getMergeList() override;
    const static QString NEW_COMPONENT_ID;

    virtual OPERATION_ATTR toXML() const override;
private:
    QString oldComponentId,newComponentName;
    QList<QPair<QString,QString> >mergePortList;
    constexpr static OperationType type=REPLACE_WITH_NEW_OPERATION;
};


#endif // REPLACEWITHNEWOPERATION_H
