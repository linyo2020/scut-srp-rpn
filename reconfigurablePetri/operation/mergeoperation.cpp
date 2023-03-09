#include "mergeoperation.h"

MergeOperation::MergeOperation(const QString& portId_1,const QString& portId_2)
    :portId1(portId_1),portId2(portId_2)
{

}

void MergeOperation::execOperation(ComponentList* componentList) const
{
    componentList->addComponentPort(portId1,portId2);
}

MergeOperation *MergeOperation::clone() const
{
    return new MergeOperation(portId1,portId2);
}

QList<QString*> MergeOperation::getArguments()
{
    return QList<QString*>{&portId1,&portId2};
}

OPERATION_ATTR MergeOperation::toXML() const
{
    OPERATION_ATTR operation;
    operation.type=type;
    operation.arguments.push_back(portId1);
    operation.arguments.push_back(portId2);
    return operation;
}
