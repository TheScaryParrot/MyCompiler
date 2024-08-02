#pragma once

#include <iostream>
#include <string>

#include "../assembly/AssemblyCode.cpp"
#include "../utils/Logger.cpp"
#include "Callable.cpp"
#include "Environment.cpp"
#include "IdentifierEnvironment.cpp"
#include "InstructionEnvironment.cpp"
#include "OrderHandler.cpp"
#include "OrderQueueStackHandler.cpp"
#include "TypeStackHandler.cpp"

class CodeGenerator : public ICodeGenerator
{
   public:
    AssemblyCode* Generate(InputFile* file)
    {
        this->orderHandler = OrderHandler(file);
        this->modeStack.Push(EModes::EXECUTE);
        this->assemblyCode = new AssemblyCode();

        while (!orderHandler.IsDone())
        {
            HandleOrder(GetNextOrder());
        }

        return assemblyCode;
    }

    virtual Order GetCurrentOrder() override { return orderHandler.GetCurrentOrder(); }
    virtual Order GetNextOrder() override
    {
        orderHandler.NextOrder();
        return orderHandler.GetCurrentOrder();
    }
    virtual void ExecuteNextOrder() override { HandleOrder(GetNextOrder()); }
    virtual Callable* GetCallable(Order& order) override
    {
        if (order.GetType() != Order::EOrderTypes::Identifier)
        {
            return instructionEnvironment.GetInstruction(order.GetName());
        }

        return identifierEnvironment.GetIdentifier(order.GetName());
    }

    virtual void PushMode(EModes mode) override { modeStack.Push(mode); }
    virtual void PopMode() override { modeStack.Pop(); }
    virtual EModes GetCurrentMode() override { return modeStack.Top(); }

    virtual void PutInFront(OrderQueue orders) override { orderHandler.PutInFront(orders); }

    virtual void IncrementOrderQueueDepth() override
    {
        orderQueueDepthCounter++;

        if (orderQueueDepthCounter >= 1 && !IsInMode(EModes::ORDER_QUEUE))
        {
            PushMode(EModes::ORDER_QUEUE);
        }
    }
    virtual void DecrementOrderQueueDepth() override
    {
        orderQueueDepthCounter--;

        if (orderQueueDepthCounter <= 0 && IsInMode(EModes::ORDER_QUEUE))
        {
            PopMode();
        }
    }
    virtual void PushNewOrderQueue() override { orderQueueStack.PushNewOrderQueue(); }
    virtual Order DequeueFromOrderQueue() override { return orderQueueStack.DequeueOrder(); }
    virtual void EnqueueInOrderQueue(Order order) override { orderQueueStack.EnqueueOrder(order); }
    virtual OrderQueue* PopOrderQueue() override { return orderQueueStack.PopOrderQueue(); }
    virtual void ClearOrderQueue() override { orderQueueStack.ClearAllOrderQueues(); }
    virtual void PutInFrontFromOrderQueue() override { orderHandler.PutInFront(orderQueueStack.DequeueOrder()); }

    virtual void AddIdentifier(std::string name, Identifier* identifier) override
    {
        identifierEnvironment.AddIdentifier(name, identifier);
    }

   private:
    OrderHandler orderHandler;

    void HandleOrder(Order order)
    {
        if (order.GetType() == Order::EOrderTypes::DirectCode)
        {
            HandleDirectCode(order);
            return;
        }

        Callable* callable = this->GetCallable(order);

        if (callable == nullptr)
        {
            if (IsInMode(EModes::ORDER_QUEUE))
            {
                EnqueueInOrderQueue(order);
                return;
            }

            if (IsInMode(EModes::COMMENT))
            {
                return;
            }

            Logger.Log("No callable found for order: " + order.GetName(), Logger::ERROR);

            return;
        }

        if (IsInMode(EModes::ORDER_QUEUE) && !callable->IsCodeStackProof())
        {
            EnqueueInOrderQueue(order);
            return;
        }

        if (IsInMode(EModes::COMMENT) && !callable->IsCommentProof())
        {
            return;
        }

        callable->Execute(this);
    }

    void HandleDirectCode(Order order)
    {
        if (IsInMode(EModes::ORDER_QUEUE))
        {
            EnqueueInOrderQueue(order);
            return;
        }

        if (IsInMode(EModes::COMMENT))
        {
            return;
        }

        this->assemblyCode->AddCode(order.GetName());
    }

    unsigned int orderQueueDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    OrderQueueStackHandler orderQueueStack = OrderQueueStackHandler();

    IdentifierEnvironment identifierEnvironment = IdentifierEnvironment();

    InstructionEnvironment instructionEnvironment = InstructionEnvironment();

    AssemblyCode* assemblyCode;
};
