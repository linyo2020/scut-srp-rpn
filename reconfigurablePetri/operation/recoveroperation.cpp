#include "recoveroperation.h"

RecoverOperation::RecoverOperation(const QString& componentId)
    :componentInstanceId(componentId)
{

}

void RecoverOperation::execOperation(ComponentList* componentList) const
{
    componentList->recoverComponent(componentInstanceId);
}

RecoverOperation *RecoverOperation::clone() const
{
    return new RecoverOperation(componentInstanceId);
}

QList<QString*> RecoverOperation::getArguments()
{
    return QList<QString*>{&componentInstanceId};
}

OPERATION_ATTR RecoverOperation::toXML() const
{
    OPERATION_ATTR operation;
    operation.type=type;
    operation.arguments.push_back(componentInstanceId);
    return operation;
}
