#include "recoveroperation.h"

RecoverOperation::RecoverOperation(QString componentId)
    :componentInstanceId(componentId)
{

}

RecoverOperation::~RecoverOperation()
{

}

void RecoverOperation::execOperation(ComponentList* componentList)
{
    componentList->recoverComponent(componentInstanceId);
}
