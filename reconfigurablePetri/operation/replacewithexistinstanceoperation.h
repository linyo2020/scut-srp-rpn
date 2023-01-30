#ifndef REPLACEWITHEXISTINSTANCEOPERATION_H
#define REPLACEWITHEXISTINSTANCEOPERATION_H

#include "baseoperation.h"
#include<QPair>

class ReplaceWithExistInstanceOperation:public BaseOperation
{
public:
    /**
     * @brief 使用被删除的实例来替换要删除的旧组件实例，并可选择合并一系列端口。若要新建自动分配编号的组件来替换，使用ReplaceWithNewOperation。
     * @param componentIdToReplace 要删除的组件id
     * @param componentIdToAdd 要加入的已有实例id
     * @param mergePortList 一系列要合并的端口
     */
    ReplaceWithExistInstanceOperation(const QString& componentIdToReplace,const QString& componentIdToAdd,const QList<QPair<QString,QString> >&mergePortList);
    ReplaceWithExistInstanceOperation(const ReplaceWithExistInstanceOperation&)=delete;
    ReplaceWithExistInstanceOperation& operator=(const ReplaceWithExistInstanceOperation&)=delete;
    virtual ~ReplaceWithExistInstanceOperation();
    virtual void execOperation(ComponentList*) const override;
    virtual ReplaceWithExistInstanceOperation* clone() const override;
private:
    QString oldComponentId,newComponentId;
    QList<QPair<QString,QString> >mergePortList;
};

#endif // REPLACEWITHEXISTINSTANCEOPERATION_H
