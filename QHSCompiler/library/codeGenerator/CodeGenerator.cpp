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
    AssemblyCode* Generate(InputFile* file);

    virtual Order GetCurrentOrder() override;
    virtual Order GetNextOrder() override;
    virtual void ExecuteNextOrder() override;
    virtual Callable* GetCallable(Order& order) override;

    virtual void PushMode(EModes mode) override;
    virtual void PopMode() override;
    virtual EModes GetCurrentMode() override;

    virtual void PutInFront(OrderQueue orders) override;

    virtual void IncrementOrderQueueDepth() override;
    virtual void DecrementOrderQueueDepth() override;
    virtual void PushNewOrderQueue() override;
    virtual Order DequeueFromOrderQueue() override;
    virtual void EnqueueInOrderQueue(Order order) override;
    virtual OrderQueue* PopOrderQueue() override;
    virtual void ClearOrderQueue() override;
    virtual void PutInFrontFromOrderQueue() override;

    virtual void AddIdentifier(std::string name, Identifier* identifier) override;

   private:
    OrderHandler orderHandler;

    void HandleOrder(Order order);
    void HandleDirectCode(Order order);

    unsigned int orderQueueDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    OrderQueueStackHandler orderQueueStack = OrderQueueStackHandler();

    IdentifierEnvironment identifierEnvironment = IdentifierEnvironment();

    InstructionEnvironment instructionEnvironment = InstructionEnvironment();

    AssemblyCode* assemblyCode;
};

AssemblyCode* CodeGenerator::Generate(InputFile* file)
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

void CodeGenerator::HandleOrder(Order order)
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

void CodeGenerator::HandleDirectCode(Order order)
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

Order CodeGenerator::GetCurrentOrder() { return orderHandler.GetCurrentOrder(); }

Order CodeGenerator::GetNextOrder()
{
    orderHandler.NextOrder();
    return orderHandler.GetCurrentOrder();
}

void CodeGenerator::ExecuteNextOrder() { HandleOrder(GetNextOrder()); }

Callable* CodeGenerator::GetCallable(Order& order)
{
    if (order.GetType() != Order::EOrderTypes::Identifier)
    {
        return instructionEnvironment.GetInstruction(order.GetName());
    }

    return identifierEnvironment.GetIdentifier(order.GetName());
}

void CodeGenerator::PushMode(EModes mode) { modeStack.Push(mode); }

void CodeGenerator::PopMode() { modeStack.Pop(); }

ICodeGenerator::EModes CodeGenerator::GetCurrentMode() { return modeStack.Top(); }

void CodeGenerator::PutInFront(OrderQueue orders) { orderHandler.PutInFront(orders); }

void CodeGenerator::IncrementOrderQueueDepth()
{
    orderQueueDepthCounter++;

    if (orderQueueDepthCounter >= 1 && !IsInMode(EModes::ORDER_QUEUE))
    {
        PushMode(EModes::ORDER_QUEUE);
    }
}

void CodeGenerator::DecrementOrderQueueDepth()
{
    orderQueueDepthCounter--;

    if (orderQueueDepthCounter <= 0 && IsInMode(EModes::ORDER_QUEUE))
    {
        PopMode();
    }
}

void CodeGenerator::PushNewOrderQueue() { orderQueueStack.PushNewOrderQueue(); }

void CodeGenerator::EnqueueInOrderQueue(Order order) { orderQueueStack.EnqueueOrder(order); }

Order CodeGenerator::DequeueFromOrderQueue() { return orderQueueStack.DequeueOrder(); }

OrderQueue* CodeGenerator::PopOrderQueue() { return orderQueueStack.PopOrderQueue(); }

void CodeGenerator::PutInFrontFromOrderQueue() { orderHandler.PutInFront(orderQueueStack.DequeueOrder()); }

void CodeGenerator::ClearOrderQueue() { orderQueueStack.ClearAllOrderQueues(); }

void CodeGenerator::AddIdentifier(std::string name, Identifier* identifier)
{
    identifierEnvironment.AddIdentifier(name, identifier);
}
