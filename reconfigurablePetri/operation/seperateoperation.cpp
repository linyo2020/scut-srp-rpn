#include "seperateoperation.h"

SeperateOperation::SeperateOperation(QString compoundPortId)
    :portToSeperate(compoundPortId)
{

}

SeperateOperation::~SeperateOperation()
{

}

void SeperateOperation::execOperation(ComponentList* componentList)
{
    componentList->seperateCompoundPort(portToSeperate);
}
