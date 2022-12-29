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
        if(QString("&&&&")==ports.first)
            ports.first=newComponentId;
        if(QString("&&&&")==ports.second)
            ports.second=newComponentId;
        componentList->addComponentPort(ports.first,ports.second);
    }
}

const QString ReplaceWithNewOperation::NEW_COMPONENT_ID=QString("&&&&");
