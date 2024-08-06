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
    void Init() {}

    enum EModes
    {
        EXECUTE,
        ORDER_QUEUE,
        COMMENT
    };

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

    void IncrementOrderQueueDepth()
    {
        orderQueueDepthCounter++;

        if (orderQueueDepthCounter >= 1 && !IsInMode(EModes::ORDER_QUEUE))
        {
            PushMode(EModes::ORDER_QUEUE);
        }
    }
    void DecrementOrderQueueDepth()
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
    void PutInFrontFromOrderQueue() { OrderHandler.PutInFront(orderQueueStack.DequeueOrder()); }

    void AddInstruction(std::string name, ICallable* instruction)
    {
        instructionEnvironment.AddCallable(name, instruction);
    }
    void AddIdentifier(std::string name, ICallable* identifier) { identifierEnvironment.AddCallable(name, identifier); }

   private:
    unsigned int orderQueueDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    OrderQueueStackHandler orderQueueStack = OrderQueueStackHandler();

    Environment identifierEnvironment = Environment();

    Environment instructionEnvironment = Environment();
} CodeGenerator;
