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
#include "TypeStackHandler.cpp"

class CodeGenerator : public ICodeGenerator
{
   public:
    AssemblyCode* Generate(InputFile* file);

   private:
    OrderHandler orderHandler;

    void HandleOrder(Order order, AssemblyCode* assemblyCode);

    void HandleIdentifier(Order order);
    void HandleCompilerInstruction(Order order);
    void HandleDirectCode(Order order, AssemblyCode* assemblyCode);

    unsigned int codeStackDepthCounter = 0;

    Stack<EModes> modeStack = Stack<EModes>();

    Stack<Queue<Order>*> codeStack = Stack<Queue<Order>*>();

    TypeStackHandler typeStack = TypeStackHandler();

    IdentifierEnvironment identifierEnvironment = IdentifierEnvironment();

    InstructionEnvironment instructionEnvironment = InstructionEnvironment();
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
    switch (order.GetType())
    {
        case Order::Identifier:
            HandleIdentifier(order);
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
        /*Callable* callable = environment.GetCallable(order.GetName());

        if (callable != nullptr && callable->IsCodeStackProof())
        {
            HandleCallable(callable, assemblyCode);
            return;
        }*/
    }

    codeStack.Top()->Enqueue(order);
}

void CodeGenerator::HandleOrderInCommentMode(Order order, AssemblyCode* assemblyCode)
{
    /*if (order.GetType() == Order::EOrderTypes::CompilerInstruction)
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
    }*/
}

void CodeGenerator::HandleIdentifier(Order order)
{
    Identifier* identifier = identifierEnvironment.GetIdentifier(order.GetName());

    if (identifier == nullptr)
    {
        return;
    }

    if (modeStack.Top() == EModes::CodeStack && !identifier->IsCodeStackProof())
    {
        codeStack.Top()->Enqueue(order);
        return;
    }

    if (modeStack.Top() == EModes::Comment && !identifier->IsCommentProof())
    {
        return;
    }

    identifier->Execute(this);
}

void CodeGenerator::HandleCompilerInstruction(Order order)
{
    Callable* instruction = instructionEnvironment.GetInstruction(order.GetName());

    if (modeStack.Top() == EModes::CodeStack && !instruction->IsCodeStackProof())
    {
        codeStack.Top()->Enqueue(order);
        return;
    }

    if (modeStack.Top() == EModes::Comment && !instruction->IsCommentProof())
    {
        return;
    }

    instruction->Execute(this);
    return;

    /*if (instruction == "enterComment")
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
    }*/

    std::cout << "Unknown compiler instruction '" << instruction << "'\n";
}

void CodeGenerator::HandleDirectCode(Order order, AssemblyCode* assemblyCode)
{
    assemblyCode->AddCode(order.GetName());
}
