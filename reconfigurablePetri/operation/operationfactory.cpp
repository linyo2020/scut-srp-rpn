#include "operationfactory.h"
#include "addoperation.h"
#include "baseoperation.h"
#include "deleteoperation.h"
#include "mergeoperation.h"
#include "recoveroperation.h"
#include "replacewithexistinstanceoperation.h"
#include "replacewithnewoperation.h"
#include "seperateoperation.h"
#include "../defs.h"

BaseOperation *OperationFactory::fromXML(const OPERATION_ATTR &operation)
{
    if(operation.type<=0||operation.type>MAX_OPERATION_TYPE)
        return nullptr;
    int argNum=operation.arguments.size();
    OperationType type=OperationType(operation.type);
    switch (type) {
    case ADD_OPERATION:
        if(argNum!=1)
            return nullptr;
        return new AddOperation(operation.arguments[0]);
    case DELETE_OPERATION:
        if(argNum!=1)
            return nullptr;
        return new DeleteOperation(operation.arguments[0]);
    case MERGE_OPERATION:
        if(argNum!=2)
            return nullptr;
        return new MergeOperation(operation.arguments[0],operation.arguments[1]);
    case RECOVER_OPERATION:
        if(argNum!=1)
            return nullptr;
        return new RecoverOperation(operation.arguments[0]);
    case REPLACE_WITH_EXIST_OPERATION:
        if(argNum!=2)
            return nullptr;
        return new ReplaceWithExistInstanceOperation(operation.arguments[0],operation.arguments[1],operation.portsToMerge);
    case REPLACE_WITH_NEW_OPERATION:
        if(argNum!=2)
            return nullptr;
        return new ReplaceWithNewOperation(operation.arguments[0],operation.arguments[1],operation.portsToMerge);
    case SEPERATE_OPERATION:
        if(argNum!=2)
            return nullptr;
        return new SeperateOperation(operation.arguments[0],operation.arguments[1]);
    default:
        return nullptr;
    }
}
