#include "replacewithexistinstanceoperation.h"


ReplaceWithExistInstanceOperation::ReplaceWithExistInstanceOperation(const QString& componentIdToReplace,const QString& componentIdToAdd,const QList<QPair<QString, QString> >& mergePortList)
    :oldComponentId(componentIdToReplace),newComponentId(componentIdToAdd),mergePortList(std::move(mergePortList))
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

QList<QString*> ReplaceWithExistInstanceOperation::getArguments()
{
    return QList<QString*>{&oldComponentId,&newComponentId};
}

QList<QPair<QString, QString> > *ReplaceWithExistInstanceOperation::getMergeList()
{
    return &mergePortList;
}

OPERATION_ATTR ReplaceWithExistInstanceOperation::toXML() const
{
    OPERATION_ATTR operation;
    operation.type=type;
    operation.arguments.push_back(oldComponentId);
    operation.arguments.push_back(newComponentId);
    operation.portsToMerge=mergePortList;
    return operation;
}
