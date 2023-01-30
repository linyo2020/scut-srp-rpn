#include "deleteoperation.h"

DeleteOperation::DeleteOperation(const QString& componentId)
    :ComponentInstanceToDelete(componentId)
{

}

DeleteOperation::~DeleteOperation()
{}

void DeleteOperation::execOperation(ComponentList* componentList) const
{
    componentList->deleteComponent(ComponentInstanceToDelete);
}

DeleteOperation *DeleteOperation::clone() const
{
    return new DeleteOperation(ComponentInstanceToDelete);
}
