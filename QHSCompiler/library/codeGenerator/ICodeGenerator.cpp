#pragma once

#include "../Order.cpp"
#include "../utils/Logger.cpp"
#include "../utils/Queue.cpp"
#include "OrderQueue.cpp"
#include "Type.cpp"

class Callable;
class Identifier;

class ICodeGenerator
{
   public:
    enum EModes
    {
        EXECUTE,
        ORDER_QUEUE,
        TYPE_STACK,
        COMMENT
    };

    virtual Order GetCurrentOrder() = 0;
    virtual Order GetNextOrder() = 0;
    virtual void ExecuteNextOrder() = 0;
    virtual Callable* GetCallable(Order& order) = 0;

    virtual void PushMode(EModes mode) = 0;
    virtual void PopMode() = 0;
    virtual EModes GetCurrentMode() = 0;
    bool IsInMode(EModes mode) { return GetCurrentMode() == mode; }

    virtual void PutInFront(OrderQueue orders) = 0;

    virtual void IncrementOrderQueueDepth() = 0;
    virtual void DecrementOrderQueueDepth() = 0;
    virtual void EnqueueInOrderQueue(Order order) = 0;
    virtual OrderQueue GetOrderQueue() = 0;
    virtual void ClearOrderQueue() = 0;
    virtual void PutInFrontFromOrderQueue() = 0;

    virtual void FromPrimaryToSecondaryOrderQueue() = 0;
    virtual void FromSecondaryToPrimaryOrderQueue() = 0;

    virtual void NewTypeStack() = 0;
    virtual std::vector<Type*> PopTypeStack() = 0;

    virtual void AddIdentifier(std::string name, Identifier* identifier) = 0;
};