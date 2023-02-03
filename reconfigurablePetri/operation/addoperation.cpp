#include "addoperation.h"

AddOperation::AddOperation(const QString& componentName)
    :newComponentName(componentName)
{

}

AddOperation::~AddOperation()
{

}

void AddOperation::execOperation(ComponentList* componentList) const
{
    componentList->addNewComponent(newComponentName);
}

AddOperation *AddOperation::clone() const
{
    return new AddOperation(newComponentName);
}

QList<QString*> AddOperation::getArguments()
{
    return QList<QString*>{&newComponentName};
}
