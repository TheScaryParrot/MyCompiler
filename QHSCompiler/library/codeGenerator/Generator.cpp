#pragma once

#include "Callable.cpp"
#include "CodeGenerator.cpp"
#include "OrderHandler.cpp"

class Generator
{
   public:
    Generator(InputFile* file)
    {
        CodeGenerator.Init();
        OrderHandler.Init(file);
        InitInstructions();
    }

    AssemblyCode* Generate()
    {
        CodeGenerator.PushMode(CodeGenerator::EModes::EXECUTE);
        this->assemblyCode = new AssemblyCode();

        while (!OrderHandler.IsDone())
        {
            Order order = OrderHandler.GetNextOrder();
            HandleOrder(order);
        }

        return assemblyCode;
    }

   private:
    AssemblyCode* assemblyCode;

    void InitInstructions()
    {
        ICallable* enterComment = new Callable();
        enterComment->SetExecuteFunction([]() { CodeGenerator.PushMode(CodeGenerator::EModes::COMMENT); });
        enterComment->SetCodeStackProof(true);
        CodeGenerator.AddInstruction("enterComment", enterComment);

        ICallable* exitComment = new Callable();
        exitComment->SetExecuteFunction(
            []()
            {
                if (!CodeGenerator.IsInMode(CodeGenerator::EModes::COMMENT))
                {
                    Logger.Log("Trying to exit comment mode while not in comment mode", Logger::ERROR);
                    return;
                }
                CodeGenerator.PopMode();
            });
        exitComment->SetCodeStackProof(true);
        CodeGenerator.AddInstruction("exitComment", exitComment);

        ICallable* enterOrderQueue = new Callable();
        enterOrderQueue->SetExecuteFunction(
            []()
            {
                Logger.Log("Entering order queue mode", Logger::DEBUG);

                // If is already in OrderQueue Mode, push the current order
                // (enterOrderQueue)
                if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE))
                {
                    CodeGenerator.EnqueueInOrderQueue(OrderHandler.GetCurrentOrder());
                }

                CodeGenerator.IncrementOrderQueueDepth();
            });
        enterOrderQueue->SetCodeStackProof(true);
        CodeGenerator.AddInstruction("enterOrderQueue", enterOrderQueue);

        ICallable* exitOrderQueue = new Callable();
        exitOrderQueue->SetExecuteFunction(
            []()
            {
                Logger.Log("Exiting order queue mode", Logger::DEBUG);

                CodeGenerator.DecrementOrderQueueDepth();

                // If is still in OrderQueue Mode, push the current orQueue //
                // (exitOrderStack) to the order queue
                if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE))
                {
                    CodeGenerator.EnqueueInOrderQueue(OrderHandler.GetCurrentOrder());
                }
            });
        exitOrderQueue->SetCodeStackProof(true);
        CodeGenerator.AddInstruction("exitOrderQueue", exitOrderQueue);

        ICallable* pushNewOrderQueue = new Callable();
        pushNewOrderQueue->SetExecuteFunction([]() { CodeGenerator.PushNewOrderQueue(); });
        CodeGenerator.AddInstruction("pushNewOrderQueue", pushNewOrderQueue);

        ICallable* pushNextOrderToOrderQueue = new Callable();
        pushNextOrderToOrderQueue->SetExecuteFunction(
            []()
            {
                Order nextOrder = OrderHandler.GetNextOrder();
                CodeGenerator.EnqueueInOrderQueue(nextOrder);
            });
        CodeGenerator.AddInstruction("pushNextOrderToOrderQueue", pushNextOrderToOrderQueue);

        ICallable* clearOrderQueue = new Callable();
        clearOrderQueue->SetExecuteFunction([]() { CodeGenerator.ClearOrderQueue(); });
        CodeGenerator.AddInstruction("clearOrderQueue", clearOrderQueue);

        ICallable* putInFrontFromOrderQueue = new Callable();
        putInFrontFromOrderQueue->SetExecuteFunction(
            []()
            {
                Logger.Log("Executing from order queue", Logger::DEBUG);
                CodeGenerator.PutInFrontFromOrderQueue();
            });
        CodeGenerator.AddInstruction("putInFrontFromOrderQueue", putInFrontFromOrderQueue);

        ICallable* assignNextIdentifier = new Callable();
        assignNextIdentifier->SetExecuteFunction(
            []()
            {
                Order nextOrder = OrderHandler.GetNextOrder();

                if (nextOrder.GetType() != Order::EOrderTypes::Identifier)
                {
                    Logger.Log("Tried assigning next identifier but next order is not identifier. Skipping assign",
                               Logger::ERROR);

                    return;
                }

                Logger.Log("Assigning next order '" + nextOrder.ToString() + "'", Logger::DEBUG);

                OrderQueue* code = CodeGenerator.PopOrderQueue();

                if (code == nullptr)
                {
                    Logger.Log("No code found for assign next identifier '" + nextOrder.ToString() + "'",
                               Logger::ERROR);
                    return;
                }

                Callable* callable = new Callable();
                callable->SetExecuteFunction([code]() { OrderHandler.PutInFront(*code); });
                CodeGenerator.AddIdentifier(nextOrder.GetName(), callable);
            });
        CodeGenerator.AddInstruction("assignNextIdentifier", assignNextIdentifier);

        ICallable* assignNextIdentifierToOneOrder = new Callable();
        assignNextIdentifierToOneOrder->SetExecuteFunction(
            []()
            {
                Order nextOrder = OrderHandler.GetNextOrder();

                if (nextOrder.GetType() != Order::EOrderTypes::Identifier)
                {
                    Logger.Log("Tried assigning next identifier but next order is not identifier . Skipping assign",
                               Logger::ERROR);

                    return;
                }

                Logger.Log("Assigning next order '" + nextOrder.ToString() + "'", Logger::DEBUG);

                OrderQueue code = OrderQueue();
                code.Enqueue(CodeGenerator.DequeueFromOrderQueue());

                Callable* callable = new Callable();
                callable->SetExecuteFunction([code]() { OrderHandler.PutInFront(code); });
                CodeGenerator.AddIdentifier(nextOrder.GetName(), callable);
            });
        CodeGenerator.AddInstruction("assignNextIdentifierToOneOrder", assignNextIdentifierToOneOrder);

        ICallable* makeNextOrderOrderQueueProof = new Callable();
        makeNextOrderOrderQueueProof->SetExecuteFunction(
            []()
            {
                Order nextOrder = OrderHandler.GetNextOrder();

                Logger.Log("Making next identifier order queue proof '" + nextOrder.ToString() + "'", Logger::DEBUG);

                ICallable* callable = CodeGenerator.GetCallable(nextOrder);

                if (callable == nullptr)
                {
                    Logger.Log(
                        "No callable found for order: " + nextOrder.GetName() + " in makeNextOrderOrderQueueProof",
                        Logger::ERROR);
                    return;
                }

                callable->SetCodeStackProof(true);
            });
        CodeGenerator.AddInstruction("makeNextOrderOrderQueueProof", makeNextOrderOrderQueueProof);

        ICallable* makeNextOrderCommentProof = new Callable();
        makeNextOrderCommentProof->SetExecuteFunction(
            []()
            {
                Order nextOrder = OrderHandler.GetNextOrder();

                Logger.Log("Making next identifier comment proof '" + nextOrder.ToString() + "'", Logger::DEBUG);

                ICallable* callable = CodeGenerator.GetCallable(nextOrder);

                if (callable == nullptr)
                {
                    Logger.Log("No callable found for order: " + nextOrder.GetName() + " in makeNextOrderCommentProof",
                               Logger::ERROR);
                    return;
                }

                callable->SetCommentProof(true);
            });
        CodeGenerator.AddInstruction("makeNextOrderCommentProof", makeNextOrderCommentProof);

        ICallable* debug = new Callable();
        debug->SetExecuteFunction([]() { Logger.Log("DEBUG PRINT", Logger::DEBUG); });
        CodeGenerator.AddInstruction("debug", debug);

        ICallable* debugStatus = new Callable();
        debugStatus->SetExecuteFunction(
            []()
            {
                Logger.Log("---DEBUG STATUS", Logger::DEBUG);
                Logger.Log("---Current order: " + OrderHandler.GetCurrentOrder().ToString(), Logger::DEBUG);
                Logger.Log("---Next order: " + OrderHandler.GetNextOrder().ToString(), Logger::DEBUG);
                Logger.Log("---Current mode: " + std::to_string(CodeGenerator.GetCurrentMode()), Logger::DEBUG);
            });
        CodeGenerator.AddInstruction("debugStatus", debugStatus);

        ICallable* activateDebugMode = new Callable();
        activateDebugMode->SetExecuteFunction([]() { Logger.SetDebug(true); });
        CodeGenerator.AddInstruction("activateDebugMode", activateDebugMode);

        ICallable* deactivateDebugMode = new Callable();
        deactivateDebugMode->SetExecuteFunction([]() { Logger.SetDebug(false); });
        CodeGenerator.AddInstruction("deactivateDebugMode", deactivateDebugMode);
    }

    void HandleOrder(Order order)
    {
        if (order.GetType() == Order::EOrderTypes::DirectCode)
        {
            HandleDirectCode(order);
            return;
        }

        ICallable* callable = CodeGenerator.GetCallable(order);

        if (callable == nullptr)
        {
            if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE))
            {
                CodeGenerator.EnqueueInOrderQueue(order);
                return;
            }

            if (CodeGenerator.IsInMode(CodeGenerator::EModes::COMMENT))
            {
                return;
            }

            Logger.Log("No callable found for order: " + order.GetName(), Logger::ERROR);

            return;
        }

        if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE) && !callable->IsCodeStackProof())
        {
            CodeGenerator.EnqueueInOrderQueue(order);
            return;
        }

        if (CodeGenerator.IsInMode(CodeGenerator::EModes::COMMENT) && !callable->IsCommentProof())
        {
            return;
        }

        callable = callable->Get();
        callable->Execute();
    }

    void HandleDirectCode(Order order)
    {
        if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE))
        {
            CodeGenerator.EnqueueInOrderQueue(order);
            return;
        }

        if (CodeGenerator.IsInMode(CodeGenerator::EModes::COMMENT))
        {
            return;
        }

        this->assemblyCode->AddCode(order.GetName());
    }
};