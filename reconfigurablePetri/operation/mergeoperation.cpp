#include "mergeoperation.h"

MergeOperation::MergeOperation(QString portId_1,QString portId_2)
    :portId1(portId_1),portId2(portId_2)
{

}

MergeOperation::~MergeOperation()
{

}

void MergeOperation::execOperation(ComponentList* componentList)
{
    componentList->addComponentPort(portId1,portId2);
}
