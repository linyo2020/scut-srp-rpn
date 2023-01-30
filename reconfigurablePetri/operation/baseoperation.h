#ifndef BASEOPERATION_H
#define BASEOPERATION_H

#include "../componentlist.h"
class BaseOperation{
public:
    BaseOperation();
    virtual ~BaseOperation();
    virtual void execOperation(ComponentList*) const=0;
    virtual BaseOperation* clone() const=0;//拷贝并返回类指针，建议用基类指针接收
};

#endif // BASEOPERATION_H
