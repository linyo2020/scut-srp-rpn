#include "replacewithexistinstanceoperation.h"


ReplaceWithExistInstanceOperation::ReplaceWithExistInstanceOperation(const QString& componentIdToReplace,const QString& componentIdToAdd,const QList<QPair<QString, QString> >& mergePortList)
    :oldComponentId(componentIdToReplace),newComponentId(componentIdToAdd),mergePortList(mergePortList)
{

}

ReplaceWithExistInstanceOperation::~ReplaceWithExistInstanceOperation()
{

}

void ReplaceWithExistInstanceOperation::execOperation(ComponentList* componentList) const
{
    componentList->deleteComponent(oldComponentId);
    componentList->recoverComponent(newComponentId);
    for(QPair<QString,QString>ports:mergePortList)
    {
        componentList->addComponentPort(ports.first,ports.second);
    }
}

ReplaceWithExistInstanceOperation *ReplaceWithExistInstanceOperation::clone() const
{
    return new ReplaceWithExistInstanceOperation(oldComponentId,newComponentId,mergePortList);
}
