#include "seperateoperation.h"

SeperateOperation::SeperateOperation(const QString& compoundPortId_1,const QString& compoundPortId_2)
    :portToSeperate_1(compoundPortId_1),portToSeperate_2(compoundPortId_2)
{

}

SeperateOperation::~SeperateOperation()
{

}

void SeperateOperation::execOperation(ComponentList* componentList) const
{
    componentList->deleteConnect(portToSeperate_1,portToSeperate_2);
}

SeperateOperation *SeperateOperation::clone() const
{
    return new SeperateOperation(portToSeperate_1,portToSeperate_2);
}
