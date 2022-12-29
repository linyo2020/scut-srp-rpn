#include "replacewithnewoperation.h"

ReplaceWithNewOperation::ReplaceWithNewOperation(QString componentIdToReplace, QString componentNameToAdd, QList<QPair<QString, QString> > mergePortList)
    :oldComponentId(componentIdToReplace),newComponentName(componentNameToAdd),mergePortList(mergePortList)
{

}

ReplaceWithNewOperation::~ReplaceWithNewOperation()
{

}

void ReplaceWithNewOperation::execOperation(ComponentList* componentList)
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

const QString ReplaceWithNewOperation::NEW_COMPONENT_ID=QString("&&&&");
