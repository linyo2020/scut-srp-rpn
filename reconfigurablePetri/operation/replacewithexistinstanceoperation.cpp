#include "replacewithexistinstanceoperation.h"


ReplaceWithExistInstanceOperation::ReplaceWithExistInstanceOperation(QString componentIdToReplace, QString componentIdToAdd, QList<QPair<QString, QString> > mergePortList)
    :oldComponentId(componentIdToReplace),newComponentId(componentIdToAdd),mergePortList(mergePortList)
{

}

ReplaceWithExistInstanceOperation::~ReplaceWithExistInstanceOperation()
{

}

void ReplaceWithExistInstanceOperation::execOperation(ComponentList* componentList)
{
    componentList->deleteComponent(oldComponentId);
    componentList->recoverComponent(newComponentId);
    for(QPair<QString,QString>ports:mergePortList)
    {
        componentList->addComponentPort(ports.first,ports.second);
    }
}
