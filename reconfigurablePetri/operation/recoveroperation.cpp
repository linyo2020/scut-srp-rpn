#include "recoveroperation.h"

RecoverOperation::RecoverOperation(const QString& componentId)
    :componentInstanceId(componentId)
{

}

RecoverOperation::~RecoverOperation()
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
