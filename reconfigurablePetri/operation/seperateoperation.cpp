#include "seperateoperation.h"

SeperateOperation::SeperateOperation(QString compoundPortId_1,QString compoundPortId_2)
    :portToSeperate_1(compoundPortId_1),portToSeperate_2(compoundPortId_2)
{

}

SeperateOperation::~SeperateOperation()
{

}

void SeperateOperation::execOperation(ComponentList* componentList)
{
    componentList->deleteConnect(portToSeperate_1,portToSeperate_2);
}
