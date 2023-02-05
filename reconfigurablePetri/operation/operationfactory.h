#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

struct OPERATION_ATTR;

class AddOperation;
class BaseOperation;
class DeleteOperation;
class MergeOperation;
class RecoverOperation;
class ReplaceWithExistInstanceOperation;
class ReplaceWithNewOperation;
class SeperateOperation;

class OperationFactory
{
public:
    explicit OperationFactory()=delete;
    static BaseOperation *fromXML(const OPERATION_ATTR &operation);
};

#endif // OPERATIONFACTORY_H
