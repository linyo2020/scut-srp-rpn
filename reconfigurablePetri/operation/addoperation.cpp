#include "addoperation.h"

AddOperation::AddOperation(QString componentName)
    :newComponentName(componentName)
{

}

AddOperation::~AddOperation()
{

}

void AddOperation::execOperation(ComponentList* componentList)
{
    componentList->addNewComponent(newComponentName);
}
