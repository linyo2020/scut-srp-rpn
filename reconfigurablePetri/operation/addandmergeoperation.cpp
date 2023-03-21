#include "addandmergeoperation.h"

AddAndMergeOperation::AddAndMergeOperation(const QString &componentName, const QList<QPair<QString, QString> > &mergePortList)
    :newComponentName(componentName),mergePortList(mergePortList)
{

}

void AddAndMergeOperation::execOperation(ComponentList *componentList) const
{
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

AddAndMergeOperation *AddAndMergeOperation::clone() const
{
    return new AddAndMergeOperation(newComponentName,mergePortList);
}

QList<QString *> AddAndMergeOperation::getArguments()
{
    return QList<QString*>{&newComponentName};
}

QList<QPair<QString, QString> > *AddAndMergeOperation::getMergeList()
{
    return &mergePortList;
}

OPERATION_ATTR AddAndMergeOperation::toXML() const
{
    OPERATION_ATTR operation;
    operation.type=type;
    operation.arguments.push_back(newComponentName);
    operation.portsToMerge=mergePortList;
    return operation;
}

