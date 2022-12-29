#ifndef BASEOPERATION_H
#define BASEOPERATION_H

#include "../componentlist.h"
class BaseOperation{
public:
    BaseOperation();
    virtual ~BaseOperation();
    virtual void execOperation(ComponentList*)=0;
};

#endif // BASEOPERATION_H
