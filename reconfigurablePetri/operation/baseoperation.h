#ifndef BASEOPERATION_H
#define BASEOPERATION_H

#include "../componentlist.h"
#include "../defs.h"
class BaseOperation{
public:
    BaseOperation();
    virtual ~BaseOperation();
    virtual void execOperation(ComponentList*) const=0;
    virtual BaseOperation* clone() const=0;//拷贝并返回类指针，建议用基类指针接收
    virtual OperationType getType()const{return type;}
    virtual QList<QString*> getArguments()=0;//在返回列表中根据声明顺序填入QString
    virtual QList<QPair<QString,QString> > *getMergeList(){return nullptr;}//两个replace操作使用

    virtual OPERATION_ATTR toXML() const=0;
private:
    constexpr static OperationType type=BASE_OPERATION;
};

#endif // BASEOPERATION_H
