#pragma once

#include <iostream>
#include <string>

#include "../assembly/AssemblyCode.cpp"
#include "../utils/Logger.cpp"
#include "Environment.cpp"
#include "OrderHandler.cpp"
#include "OrderQueueStackHandler.cpp"

static class CodeGenerator
{
   public:
    void Init(InputFile* file, AssemblyCode* assemblyCode)
    {
        this->orderHandler = new OrderHandler(file);
        this->assemblyCode = assemblyCode;
    }
    ~CodeGenerator() { delete orderHandler; }

    enum EModes
    {
        EXECUTE,
        ORDER_QUEUE,
        COMMENT
    };

    bool IsDone() { return orderHandler->IsDone(); }
    Order GetNextOrder(bool checkForMode = true)
    {
        Order newOrder = orderHandler->GetNextOrder();
        currentOrder = newOrder;

        // If the order has a callable and is not in OrderQueue or Comment, call ICallable::Encounter()
        if (newOrder.GetType() == Order::EOrderTypes::DirectCode) return currentOrder;

        ICallable* callable = GetCallable(newOrder);
        if (callable == nullptr) return currentOrder;

        if (IsInMode(EModes::COMMENT) && checkForMode && !callable->IsCommentProof()) return currentOrder;
        if (IsInMode(EModes::ORDER_QUEUE) && checkForMode && !callable->IsOrderQueueProof()) return currentOrder;

        callable->Encounter();
        return currentOrder;
    }
    Order GetCurrentOrder() { return currentOrder; }
    void SetCurrentOrder(Order order) { currentOrder = order; }
    void IncrementOrderHandlerStackDepth() { orderHandler->IncrementOrderStackDepth(); }
    void DecreaseOrderHandlerStackDepth() { orderHandler->DecreaseOrderStackDepth(); }

    void HandleOrder(Order order, bool checkForMode)
    {
        if (order.GetType() == Order::EOrderTypes::DirectCode)
        {
            HandleDirectCode(order, checkForMode);
            return;
        }

        ICallable* callable = GetCallable(order);

        if (callable == nullptr)
        {
            if (IsInMode(EModes::COMMENT) && checkForMode)
            {
                return;
            }

            if (IsInMode(EModes::ORDER_QUEUE) && checkForMode)
            {
                EnqueueInOrderQueue(order);
                return;
            }

            Logger.Log("No callable found for order: " + order.GetName(), Logger::ERROR);

            return;
        }

        if (IsInMode(EModes::COMMENT) && checkForMode && !callable->IsCommentProof())
        {
            return;
        }

        if (IsInMode(EModes::ORDER_QUEUE) && checkForMode && !callable->IsOrderQueueProof())
        {
            EnqueueInOrderQueue(order);
            return;
        }

        callable->Execute();
    }

    void HandleDirectCode(Order order, bool checkForMode)
    {
        if (IsInMode(EModes::ORDER_QUEUE) && checkForMode)
        {
            EnqueueInOrderQueue(order);
            return;
        }

        if (IsInMode(EModes::COMMENT) && checkForMode)
        {
            return;
        }

        this->assemblyCode->AddCode(order.GetName());
    }

    ICallable* GetCallable(Order& order)
    {
        if (order.GetType() != Order::EOrderTypes::Identifier)
        {
            return instructionEnvironment.GetCallable(order.GetName());
        }

        return identifierEnvironment.GetCallable(order.GetName());
    }

    void PushMode(EModes mode) { modeStack.Push(mode); }
    void PopMode() { modeStack.Pop(); }
    EModes GetCurrentMode() { return modeStack.Top(); }
    bool IsInMode(EModes mode) { return GetCurrentMode() == mode; }

    void PutInFront(Order order) { orderHandler->PutInFront(order); }
    void PutInFront(OrderQueue orderQueue) { orderHandler->PutInFront(orderQueue); }

    void IncrementOrderQueueMode()
    {
        orderQueueDepthCounter++;

        if (orderQueueDepthCounter >= 1 && !IsInMode(EModes::ORDER_QUEUE))
        {
            PushMode(EModes::ORDER_QUEUE);
        }
    }
    void DecrementOrderQueueMode()
    {
        orderQueueDepthCounter--;

        if (orderQueueDepthCounter <= 0 && IsInMode(EModes::ORDER_QUEUE))
        {
            PopMode();
        }
    }
    void PushNewOrderQueue() { orderQueueStack.PushNewOrderQueue(); }
    Order DequeueFromOrderQueue() { return orderQueueStack.DequeueOrder(); }
    void EnqueueInOrderQueue(Order order) { orderQueueStack.EnqueueOrder(order); }
    OrderQueue* PopOrderQueue() { return orderQueueStack.PopOrderQueue(); }
    void ClearOrderQueue() { orderQueueStack.ClearAllOrderQueues(); }
    void PutInFrontFromOrderQueue() { orderHandler->PutInFront(orderQueueStack.DequeueOrder()); }

    void AddInstruction(std::string name, ICallable* instruction)
    {
        instructionEnvironment.AddCallable(name, instruction);
    }
    void AddIdentifier(std::string name, ICallable* identifier) { identifierEnvironment.AddCallable(name, identifier); }

   private:
    AssemblyCode* assemblyCode;

    unsigned int orderQueueDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    OrderQueueStackHandler orderQueueStack = OrderQueueStackHandler();

    Environment identifierEnvironment = Environment();

    Environment instructionEnvironment = Environment();

    OrderHandler* orderHandler;
    Order currentOrder = Order::Empty();
} CodeGenerator;
