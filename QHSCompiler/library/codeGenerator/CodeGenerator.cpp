#pragma once

#include <iostream>
#include <string>

#include "../OrderQueue.cpp"
#include "../assembly/AssemblyCode.cpp"
#include "Callable.cpp"
#include "Environment.cpp"
#include "TypeStackHandler.cpp"

class CodeGenerator
{
   public:
    CodeGenerator();
    AssemblyCode* GenerateOrders(OrderQueue orders);

   private:
    void HandleOrder(OrderQueue* orders, AssemblyCode* assemblyCode);
    void HandleOrderInCallableStackMode(OrderQueue* orders, AssemblyCode* assemblyCode);
    void HandleOrderInCodeStackMode(OrderQueue* orders, AssemblyCode* assemblyCode);
    void HandleOrderInTypeStackMode(OrderQueue* orders, AssemblyCode* assemblyCode);
    void HandleOrderInCommentMode(OrderQueue* orders, AssemblyCode* assemblyCode);

    void HandleIdentifier(OrderQueue* orders, AssemblyCode* assemblyCode);
    void HandleCompilerInstruction(OrderQueue* orders);

    void HandleCallable(Callable* callable, OrderQueue* orders, AssemblyCode* assemblyCode);

    enum EModes
    {
        CallableStack,
        CodeStack,
        TypeStack,
        DirectCode,
        Comment
    };

    unsigned int codeStackDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    Stack<OrderQueue*> codeStack = Stack<OrderQueue*>();

    TypeStackHandler typeStack = TypeStackHandler();

    Environment environment = Environment();
};

CodeGenerator::CodeGenerator() { modeStack.Push(EModes::CallableStack); }

AssemblyCode* CodeGenerator::GenerateOrders(OrderQueue orders)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    while (!orders.IsEmpty())
    {
        HandleOrder(&orders, assemblyCode);
    }

    return assemblyCode;
}

void CodeGenerator::HandleOrder(OrderQueue* orders, AssemblyCode* assemblyCode)
{
    if (modeStack.Top() == EModes::CodeStack)
    {
        HandleOrderInCodeStackMode(orders, assemblyCode);
        return;
    }

    if (modeStack.Top() == EModes::TypeStack)
    {
        HandleOrderInTypeStackMode(orders, assemblyCode);
        return;
    }

    if (modeStack.Top() == EModes::CallableStack)
    {
        HandleOrderInCallableStackMode(orders, assemblyCode);
        return;
    }

    if (modeStack.Top() == EModes::Comment)
    {
        HandleOrderInCommentMode(orders, assemblyCode);
        return;
    }
}

void CodeGenerator::HandleOrderInCallableStackMode(OrderQueue* orders, AssemblyCode* assemblyCode)
{
    switch (orders->Front().GetType())
    {
        case Order::Identifier:
            HandleIdentifier(orders, assemblyCode);
            break;
        case Order::CompilerInstruction:
            HandleCompilerInstruction(orders);
            break;
    }
}

void CodeGenerator::HandleOrderInCodeStackMode(OrderQueue* orders, AssemblyCode* assemblyCode)
{
    Order order = orders->Pop();

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
            Order nextOrder = orders->Pop();
            codeStack.Top()->Push(nextOrder);
            return;
        }

        if (codeStackDepthCounter <= 0)
        {
            std::cout << "Exiting code stack\n";
            modeStack.Pop();
            return;
        }
    }
    else if (order.GetType() == Order::EOrderTypes::Identifier)
    {
        Callable* callable = environment.GetCallable(order.GetName());

        if (callable != nullptr && callable->IsCodeStackProof())
        {
            HandleCallable(callable, orders, assemblyCode);
            return;
        }
    }

    codeStack.Top()->Push(order);
}

void CodeGenerator::HandleOrderInTypeStackMode(OrderQueue* orders, AssemblyCode* assemblyCode)
{
    switch (orders->Front().GetType())
    {
        case Order::Identifier:
            HandleIdentifier(orders, assemblyCode);
            break;
        case Order::CompilerInstruction:
            HandleCompilerInstruction(orders);
            break;
    }
}

void CodeGenerator::HandleOrderInCommentMode(OrderQueue* orders, AssemblyCode* assemblyCode)
{
    Order order = orders->Pop();

    if (order.GetType() == Order::EOrderTypes::CompilerInstruction)
    {
        std::string instruction = order.GetName();

        if (instruction == "exitComment")
        {
            std::cout << "Exiting comment\n";
            modeStack.Pop();
        }
    }
    else if (order.GetType() == Order::EOrderTypes::Identifier)
    {
        Callable* callable = environment.GetCallable(order.GetName());

        if (callable != nullptr && callable->IsCommentProof())
        {
            HandleCallable(callable, orders, assemblyCode);
        }
    }
}

void CodeGenerator::HandleIdentifier(OrderQueue* orders, AssemblyCode* assemblyCode)
{
    Order order = orders->Pop();

    Callable* callable = environment.GetCallable(order.GetName());

    if (callable == nullptr)
    {
        std::cerr << "Unknown identifier '" << order.GetName() << "'\n";
        return;
    }

    HandleCallable(callable, orders, assemblyCode);
}

void CodeGenerator::HandleCompilerInstruction(OrderQueue* orders)
{
    Order order = orders->Pop();

    std::string instruction = order.GetName();

    if (instruction == "enterComment")
    {
        std::cout << "Entering comment\n";
        modeStack.Push(EModes::Comment);
        return;
    }

    if (instruction == "exitComment")
    {
        std::cerr << "Exiting comment called although not in CommentMode. Exiting comment should be handled by "
                     "HandleOrderInCommentMode\n";
        return;
    }

    if (instruction == "enterCodeStack")
    {
        std::cout << "Entering code stack\n";
        codeStack.Push(new OrderQueue());
        modeStack.Push(EModes::CodeStack);
        codeStackDepthCounter = 1;
        return;
    }

    if (instruction == "exitCodeStack")
    {
        std::cout << "Exiting code stack called although not in CodeStackMode. Exiting code stack should be handled by "
                     "HandleOrderInCodeStackMode\n";

        return;
    }

    if (instruction == "enterTypeStack")
    {
        std::cout << "Entering type stack\n";
        typeStack.NewStack();
        modeStack.Push(EModes::TypeStack);
        return;
    }

    if (instruction == "pushNextOrderToCodeStack")
    {
        std::cout << "Trying to push next order to code stack. But not in codeStackMode. This instruction is only "
                     "valid in code stack mode\n";
        return;
    }

    if (instruction == "exitTypeStack")
    {
        std::cout << "Exiting type stack\n";
        modeStack.Pop();
        return;
    }

    if (instruction == "assignNextIdentifier")
    {
        Order nextOrder = orders->Pop();

        if (nextOrder.GetType() == Order::EOrderTypes::CompilerInstruction)
        {
            std::cerr << "Tried assigning next identifier but identifier '" << nextOrder.ToString()
                      << "' is compiler instruction\n";
            return;
        }

        std::cout << "Assigning next order '" << nextOrder.ToString() << "'\n";

        std::vector<Type*> popTypes = typeStack.PopStack();
        std::vector<Type*> pushTypes = typeStack.PopStack();
        OrderQueue* code = codeStack.Pop();

        Callable* callable = new Callable(pushTypes, popTypes, *code);

        environment.AddCallable(nextOrder.GetName(), callable);

        return;
    }

    if (instruction == "makeNextIdentifierCodeStackProof")
    {
        Order nextOrder = orders->Pop();

        if (nextOrder.GetType() == Order::EOrderTypes::CompilerInstruction)
        {
            std::cerr << "Tried making next identifier code stack proof but identifier '" << nextOrder.ToString()
                      << "' is compiler instruction\n";
            return;
        }

        std::cout << "Making next order '" << nextOrder.ToString() << "' code stack proof\n";

        Callable* callable = environment.GetCallable(nextOrder.GetName());
        callable->MakeCodeStackProof();
        return;
    }

    if (instruction == "makeNextIdentifierCommentProof")
    {
        Order nextOrder = orders->Pop();

        if (nextOrder.GetType() == Order::EOrderTypes::CompilerInstruction)
        {
            std::cerr << "Tried making next identifier comment proof but identifier '" << nextOrder.ToString()
                      << "' is compiler instruction\n";
            return;
        }

        std::cout << "Making next order '" << nextOrder.ToString() << "' comment proof\n";

        Callable* callable = environment.GetCallable(nextOrder.GetName());
        callable->MakeCommentProof();
        return;
    }

    if (instruction == "debug")
    {
        std::cout << "DEBUG PRINT\n";
        return;
    }

    if (instruction == "debugStatus")
    {
        std::cout << "---DEBUG STATUS\n";
        std::cout << "---Mode: " << modeStack.Top() << "\n";
        std::cout << "---CodeStackDepthCounter: " << codeStackDepthCounter << "\n";
        return;
    }

    std::cout << "Unknown compiler instruction '" << instruction << "'\n";
}

void CodeGenerator::HandleCallable(Callable* callable, OrderQueue* orders, AssemblyCode* assemblyCode)
{
    OrderQueue code = callable->GetOrders();
    orders->PushFrontQueue(code);
}
