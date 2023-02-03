#ifndef MERGEOPERATION_H
#define MERGEOPERATION_H

#include "baseoperation.h"

//合并端口
class MergeOperation:public BaseOperation
{
public:
    MergeOperation(const QString& portId_1,const QString& portId_2);
    MergeOperation(const MergeOperation&)=delete;
    MergeOperation& operator=(const MergeOperation&)=delete;
    virtual ~MergeOperation();
    virtual void execOperation(ComponentList*) const override;
    virtual MergeOperation* clone() const override;
    virtual OperationType getType()const override{return type;}
private:
    QString portId1,portId2;
    constexpr static OperationType type=MERGE_OPERATION;
};

#endif // MERGEOPERATION_H
