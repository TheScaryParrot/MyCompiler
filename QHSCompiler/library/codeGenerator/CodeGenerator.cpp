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
#include "OrderStackHandler.cpp"
#include "TypeStackHandler.cpp"

class CodeGenerator : public ICodeGenerator
{
   public:
    AssemblyCode* Generate(InputFile* file);

    virtual Order GetCurrentOrder() override;
    virtual Order GetNextOrder() override;
    virtual Callable* GetCallable(Order& order) override;

    virtual void PushMode(EModes mode) override;
    virtual void PopMode() override;
    virtual EModes GetCurrentMode() override;

    virtual void PutInFront(OrderQueue orders) override;

    virtual void IncrementCodeStackDepth() override;
    virtual void DecrementCodeStackDepth() override;
    virtual void PushToOrderStack(Order order) override;
    virtual OrderQueue PopFromCodeStack() override;

    virtual void NewTypeStack() override;
    virtual std::vector<Type*> PopTypeStack() override;

    virtual void AddIdentifier(std::string name, Identifier* identifier) override;

   private:
    OrderHandler orderHandler;

    void HandleOrder(Order order, AssemblyCode* assemblyCode);
    void HandleDirectCode(Order order, AssemblyCode* assemblyCode);

    unsigned int codeStackDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    OrderStackHandler orderStackHandler = OrderStackHandler();

    TypeStackHandler typeStack = TypeStackHandler();

    IdentifierEnvironment identifierEnvironment = IdentifierEnvironment();

    InstructionEnvironment instructionEnvironment = InstructionEnvironment();
};

AssemblyCode* CodeGenerator::Generate(InputFile* file)
{
    this->orderHandler = OrderHandler(file);
    this->modeStack.Push(EModes::CallableStack);
    this->orderStackHandler.NewStack();

    AssemblyCode* assemblyCode = new AssemblyCode();

    while (!orderHandler.IsDone())
    {
        HandleOrder(orderHandler.GetCurrentOrder(), assemblyCode);
        orderHandler.NextOrder();
    }

    return assemblyCode;
}

void CodeGenerator::HandleOrder(Order order, AssemblyCode* assemblyCode)
{
    if (order.GetType() == Order::EOrderTypes::DirectCode)
    {
        HandleDirectCode(order, assemblyCode);
        return;
    }

    Callable* callable = this->GetCallable(order);

    if (callable == nullptr)
    {
        return;
    }

    if (IsInMode(EModes::CodeStack) && !callable->IsCodeStackProof())
    {
        PushToOrderStack(order);
        return;
    }

    if (IsInMode(EModes::Comment) && !callable->IsCommentProof())
    {
        return;
    }

    callable->Execute(this);
}

void CodeGenerator::HandleDirectCode(Order order, AssemblyCode* assemblyCode)
{
    if (IsInMode(EModes::CodeStack))
    {
        PushToOrderStack(order);
        return;
    }

    if (IsInMode(EModes::Comment))
    {
        return;
    }

    assemblyCode->AddCode(order.GetName());
}

Order CodeGenerator::GetCurrentOrder() { return orderHandler.GetCurrentOrder(); }

Order CodeGenerator::GetNextOrder()
{
    orderHandler.NextOrder();
    return orderHandler.GetCurrentOrder();
}

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

void CodeGenerator::IncrementCodeStackDepth()
{
    codeStackDepthCounter++;

    if (codeStackDepthCounter >= 1 && !IsInMode(EModes::CodeStack))
    {
        orderStackHandler.NewStack();
        PushMode(EModes::CodeStack);
    }
}

void CodeGenerator::DecrementCodeStackDepth()
{
    codeStackDepthCounter--;

    if (codeStackDepthCounter <= 0 && IsInMode(EModes::CodeStack))
    {
        PopMode();
    }
}

void CodeGenerator::PushToOrderStack(Order order) { orderStackHandler.PushOrder(order); }

OrderQueue CodeGenerator::PopFromCodeStack() { return orderStackHandler.PopOrderQueue(); }

void CodeGenerator::NewTypeStack() { typeStack.NewStack(); }

std::vector<Type*> CodeGenerator::PopTypeStack() { return typeStack.PopStack(); }

void CodeGenerator::AddIdentifier(std::string name, Identifier* identifier)
{
    identifierEnvironment.AddIdentifier(name, identifier);
}
