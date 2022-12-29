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
    ReplaceWithNewOperation(QString componentIdToReplace,QString componentNameToAdd,QList<QPair<QString,QString> >mergePortList);
    virtual ~ReplaceWithNewOperation();
    virtual void execOperation(ComponentList*);
    const static QString NEW_COMPONENT_ID;
private:
    QString oldComponentId,newComponentName;
    QList<QPair<QString,QString> >mergePortList;
};


#endif // REPLACEWITHNEWOPERATION_H
