#pragma once

#include <iostream>
#include <string>

#include "../assembly/AssemblyCode.cpp"
#include "../utils/Logger.cpp"
#include "Callable.cpp"
#include "Environment.cpp"
#include "OrderHandler.cpp"
#include "TypeStackHandler.cpp"

class CodeGenerator
{
   public:
    AssemblyCode* Generate(InputFile* file);

   private:
    OrderHandler orderHandler;

    void HandleOrder(Order order, AssemblyCode* assemblyCode);
    void HandleOrderInCallableStackMode(Order order, AssemblyCode* assemblyCode);
    void HandleOrderInCodeStackMode(Order order, AssemblyCode* assemblyCode);
    void HandleOrderInTypeStackMode(Order order, AssemblyCode* assemblyCode);
    void HandleOrderInCommentMode(Order order, AssemblyCode* assemblyCode);

    void HandleIdentifier(Order order, AssemblyCode* assemblyCode);
    void HandleCompilerInstruction(Order order);
    void HandleDirectCode(Order order, AssemblyCode* assemblyCode);

    void HandleCallable(Callable* callable, AssemblyCode* assemblyCode);

    enum EModes
    {
        CallableStack,
        CodeStack,
        TypeStack,
        Comment
    };

    unsigned int codeStackDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    Stack<Queue<Order>*> codeStack = Stack<Queue<Order>*>();

    TypeStackHandler typeStack = TypeStackHandler();

    Environment environment = Environment();
};

AssemblyCode* CodeGenerator::Generate(InputFile* file)
{
    this->orderHandler = OrderHandler(file);
    this->modeStack.Push(EModes::CallableStack);

    AssemblyCode* assemblyCode = new AssemblyCode();

    while (!orderHandler.IsDone())
    {
        HandleOrder(orderHandler.GetNextOrder(), assemblyCode);
    }

    return assemblyCode;
}

void CodeGenerator::HandleOrder(Order order, AssemblyCode* assemblyCode)
{
    if (modeStack.Top() == EModes::CodeStack)
    {
        HandleOrderInCodeStackMode(order, assemblyCode);
        return;
    }

    if (modeStack.Top() == EModes::TypeStack)
    {
        HandleOrderInTypeStackMode(order, assemblyCode);
        return;
    }

    if (modeStack.Top() == EModes::CallableStack)
    {
        HandleOrderInCallableStackMode(order, assemblyCode);
        return;
    }

    if (modeStack.Top() == EModes::Comment)
    {
        HandleOrderInCommentMode(order, assemblyCode);
        return;
    }
}

void CodeGenerator::HandleOrderInCallableStackMode(Order order, AssemblyCode* assemblyCode)
{
    switch (order.GetType())
    {
        case Order::Identifier:
            HandleIdentifier(order, assemblyCode);
            break;
        case Order::CompilerInstruction:
            HandleCompilerInstruction(order);
            break;
        case Order::DirectCode:
            HandleDirectCode(order, assemblyCode);
            break;
    }
}

void CodeGenerator::HandleOrderInCodeStackMode(Order order, AssemblyCode* assemblyCode)
{
    if (order.GetType() == Order::EOrderTypes::CompilerInstruction)
    {
        std::string instruction = order.GetName();

        if (instruction == "exitCodeStack")
        {
            codeStackDepthCounter--;
        }

        if (instruction == "enterCodeStack")
        {
            codeStackDepthCounter++;
        }

        if (instruction == "pushNextOrderToCodeStack")
        {
            Order nextOrder = orderHandler.GetNextOrder();
            codeStack.Top()->Enqueue(nextOrder);
            return;
        }

        if (codeStackDepthCounter <= 0)
        {
            Logger.Log("Exiting code stack", Logger::DEBUG);
            modeStack.Pop();
            return;
        }
    }
    else if (order.GetType() == Order::EOrderTypes::Identifier)
    {
        Callable* callable = environment.GetCallable(order.GetName());

        if (callable != nullptr && callable->IsCodeStackProof())
        {
            HandleCallable(callable, assemblyCode);
            return;
        }
    }

    codeStack.Top()->Enqueue(order);
}

void CodeGenerator::HandleOrderInTypeStackMode(Order order, AssemblyCode* assemblyCode)
{
    switch (order.GetType())
    {
        case Order::Identifier:
            HandleIdentifier(order, assemblyCode);
            break;
        case Order::CompilerInstruction:
            HandleCompilerInstruction(order);
            break;
        case Order::DirectCode:
            HandleDirectCode(order, assemblyCode);
            break;
    }
}

void CodeGenerator::HandleOrderInCommentMode(Order order, AssemblyCode* assemblyCode)
{
    if (order.GetType() == Order::EOrderTypes::CompilerInstruction)
    {
        std::string instruction = order.GetName();

        if (instruction == "exitComment")
        {
            Logger.Log("Exiting comment", Logger::DEBUG);
            modeStack.Pop();
        }
    }
    else if (order.GetType() == Order::EOrderTypes::Identifier)
    {
        Callable* callable = environment.GetCallable(order.GetName());

        if (callable != nullptr && callable->IsCommentProof())
        {
            HandleCallable(callable, assemblyCode);
        }
    }
}

void CodeGenerator::HandleIdentifier(Order order, AssemblyCode* assemblyCode)
{
    Callable* callable = environment.GetCallable(order.GetName());

    if (callable == nullptr)
    {
        Logger.Log("Unknown identifier '" + order.GetName() + "'", Logger::ERROR);
        return;
    }

    HandleCallable(callable, assemblyCode);
}

void CodeGenerator::HandleCompilerInstruction(Order order)
{
    std::string instruction = order.GetName();

    if (instruction == "enterComment")
    {
        Logger.Log("Entering Comment", Logger::DEBUG);
        modeStack.Push(EModes::Comment);
        return;
    }

    if (instruction == "exitComment")
    {
        Logger.Log(
            "Exiting comment called although not in CommentMode. Exiting comment should be handled by "
            "HandleOrderInCommentMode",
            Logger::WARNING);
        return;
    }

    if (instruction == "enterCodeStack")
    {
        Logger.Log("Entering CodeStack", Logger::DEBUG);
        codeStack.Push(new Queue<Order>());
        modeStack.Push(EModes::CodeStack);
        codeStackDepthCounter = 1;
        return;
    }

    if (instruction == "exitCodeStack")
    {
        Logger.Log(
            "Exiting code stack called although not in CodeStackMode. Exiting code stack should be handled by "
            "HandleOrderInCodeStackMode",
            Logger::WARNING);

        return;
    }

    if (instruction == "enterTypeStack")
    {
        Logger.Log("Entering TypeStack", Logger::DEBUG);
        typeStack.NewStack();
        modeStack.Push(EModes::TypeStack);
        return;
    }

    if (instruction == "pushNextOrderToCodeStack")
    {
        Logger.Log(
            "Trying to push next order to code stack. But not in codeStackMode. This instruction is only "
            "valid in code stack mode",
            Logger::WARNING);
        return;
    }

    if (instruction == "exitTypeStack")
    {
        Logger.Log("Exiting TypeStack", Logger::DEBUG);
        modeStack.Pop();
        return;
    }

    if (instruction == "assignNextIdentifier")
    {
        Order nextOrder = orderHandler.GetNextOrder();

        if (nextOrder.GetType() == Order::EOrderTypes::CompilerInstruction)
        {
            Logger.Log("Tried assigning next identifier but identifier is compiler instruction. Skipping assign",
                       Logger::ERROR);

            return;
        }

        Logger.Log("Assigning next order '" + nextOrder.ToString() + "'", Logger::DEBUG);

        std::vector<Type*> popTypes = typeStack.PopStack();
        std::vector<Type*> pushTypes = typeStack.PopStack();
        Queue<Order>* code = codeStack.Pop();

        Callable* callable = new Callable(pushTypes, popTypes, *code);
        delete code;

        environment.AddCallable(nextOrder.GetName(), callable);

        return;
    }

    if (instruction == "makeNextIdentifierCodeStackProof")
    {
        Order nextOrder = orderHandler.GetNextOrder();

        if (nextOrder.GetType() == Order::EOrderTypes::CompilerInstruction)
        {
            Logger.Log("Tried making next identifier code stack proof but identifier '" + nextOrder.ToString() +
                           "' is compiler instruction",
                       Logger::ERROR);
            return;
        }

        Logger.Log("Making next order '" + nextOrder.ToString() + "' code stack proof", Logger::DEBUG);

        Callable* callable = environment.GetCallable(nextOrder.GetName());
        callable->MakeCodeStackProof();
        return;
    }

    if (instruction == "makeNextIdentifierCommentProof")
    {
        Order nextOrder = orderHandler.GetNextOrder();

        if (nextOrder.GetType() == Order::EOrderTypes::CompilerInstruction)
        {
            Logger.Log("Tried making next identifier comment proof but identifier '" + nextOrder.ToString() +
                           "' is compiler instruction",
                       Logger::ERROR);
            return;
        }

        Logger.Log("Making next order '" + nextOrder.ToString() + "' comment proof", Logger::DEBUG);

        Callable* callable = environment.GetCallable(nextOrder.GetName());
        callable->MakeCommentProof();
        return;
    }

    if (instruction == "debug")
    {
        Logger.Log("DEBUG PRINT", Logger::INFO);
        return;
    }

    if (instruction == "debugStatus")
    {
        Logger.Log("---DEBUG STATUS", Logger::INFO);
        Logger.Log("---Mode: " + std::to_string(modeStack.Top()), Logger::INFO);
        Logger.Log("---CodeStackDepthCounter: " + std::to_string(codeStackDepthCounter), Logger::INFO);
        return;
    }

    if (instruction == "activateDebugMode")
    {
        Logger.SetDebug(true);
        return;
    }

    if (instruction == "deactivateDebugMode")
    {
        Logger.SetDebug(false);
        return;
    }

    std::cout << "Unknown compiler instruction '" << instruction << "'\n";
}

void CodeGenerator::HandleDirectCode(Order order, AssemblyCode* assemblyCode)
{
    assemblyCode->AddCode(order.GetName());
}

void CodeGenerator::HandleCallable(Callable* callable, AssemblyCode* assemblyCode)
{
    orderHandler.PutInFront(callable->GetOrders());
}
