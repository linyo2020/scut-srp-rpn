#include "deleteoperation.h"

DeleteOperation::DeleteOperation(QString componentId)
    :ComponentInstanceToDelete(componentId)
{

}

DeleteOperation::~DeleteOperation()
{}

void DeleteOperation::execOperation(ComponentList* componentList)
{
    componentList->deleteComponent(ComponentInstanceToDelete);
}
