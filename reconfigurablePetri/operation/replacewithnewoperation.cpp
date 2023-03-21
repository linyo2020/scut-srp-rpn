#include "replacewithnewoperation.h"

ReplaceWithNewOperation::ReplaceWithNewOperation(const QString& componentIdToReplace,const QString& componentNameToAdd,const QList<QPair<QString, QString> >& mergePortList)
    :oldComponentId(componentIdToReplace),newComponentName(componentNameToAdd),mergePortList(mergePortList)
{

}

void ReplaceWithNewOperation::execOperation(ComponentList* componentList) const
{
    componentList->deleteComponent(oldComponentId);
    QString newComponentId=componentList->addNewComponent(newComponentName);
    for(QPair<QString,QString>ports:mergePortList)
    {
        if(ports.first.contains(NEW_COMPONENT_ID))
            ports.first=newComponentId+ports.first.mid(NEW_COMPONENT_ID.size());
        if(ports.second.contains(NEW_COMPONENT_ID))
            ports.second=newComponentId+ports.second.mid(NEW_COMPONENT_ID.size());
        componentList->addComponentPort(ports.first,ports.second);
    }
}

ReplaceWithNewOperation *ReplaceWithNewOperation::clone() const
{
    return new ReplaceWithNewOperation(oldComponentId,newComponentName,mergePortList);
}

QList<QString*> ReplaceWithNewOperation::getArguments()
{
    return QList<QString*>{&oldComponentId,&newComponentName};
}

QList<QPair<QString, QString> > *ReplaceWithNewOperation::getMergeList()
{
    return &mergePortList;
}

OPERATION_ATTR ReplaceWithNewOperation::toXML() const
{
    OPERATION_ATTR operation;
    operation.type=type;
    operation.arguments.push_back(oldComponentId);
    operation.arguments.push_back(newComponentName);
    operation.portsToMerge=mergePortList;
    return operation;
}

