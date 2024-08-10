#pragma once

#include "Callable.cpp"
#include "CodeGenerator.cpp"

class Generator
{
   public:
    Generator(InputFile* file)
    {
        this->assemblyCode = new AssemblyCode();
        CodeGenerator.Init(file, assemblyCode);
        InitInstructions();
    }

    AssemblyCode* Generate()
    {
        CodeGenerator.PushMode(CodeGenerator::EModes::EXECUTE);

        while (!CodeGenerator.IsDone())
        {
            CodeGenerator.HandleOrder(CodeGenerator.GetNextOrder(), true);
        }

        return assemblyCode;
    }

   private:
    AssemblyCode* assemblyCode;

    void InitInstructions()
    {
#pragma region Comment

        ICallable* enterComment = new Callable();
        enterComment->SetExecuteFunction([]() { CodeGenerator.PushMode(CodeGenerator::EModes::COMMENT); });
        enterComment->SetOrderQueueProof(true);
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
        exitComment->SetOrderQueueProof(true);
        exitComment->SetCommentProof(true);
        CodeGenerator.AddInstruction("exitComment", exitComment);

#pragma endregion
#pragma region OrderQueue
        ICallable* enterOrderQueue = new Callable();
        enterOrderQueue->SetExecuteFunction(
            []()
            {
                Logger.Log("Entering order queue mode", Logger::DEBUG);

                // If is already in OrderQueue Mode, push the current order
                // (enterOrderQueue)
                if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE))
                {
                    CodeGenerator.EnqueueInOrderQueue(CodeGenerator.GetCurrentOrder());
                }

                CodeGenerator.IncrementOrderQueueMode();
            });
        enterOrderQueue->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("enterOrderQueue", enterOrderQueue);

        ICallable* exitOrderQueue = new Callable();
        exitOrderQueue->SetExecuteFunction(
            []()
            {
                Logger.Log("Exiting order queue mode", Logger::DEBUG);

                CodeGenerator.DecrementOrderQueueMode();

                // If is still in OrderQueue Mode, push the current orQueue //
                // (exitOrderStack) to the order queue
                if (CodeGenerator.IsInMode(CodeGenerator::EModes::ORDER_QUEUE))
                {
                    CodeGenerator.EnqueueInOrderQueue(CodeGenerator.GetCurrentOrder());
                }
            });
        exitOrderQueue->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("exitOrderQueue", exitOrderQueue);

        ICallable* pushNewOrderQueue = new Callable();
        pushNewOrderQueue->SetExecuteFunction([]() { CodeGenerator.PushNewOrderQueue(); });
        CodeGenerator.AddInstruction("pushNewOrderQueue", pushNewOrderQueue);

        ICallable* pushNextOrderToOrderQueue = new Callable();
        pushNextOrderToOrderQueue->SetExecuteFunction(
            []() { CodeGenerator.EnqueueInOrderQueue(CodeGenerator.GetNextOrder()); });
        pushNextOrderToOrderQueue->SetOrderQueueProof(true);
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

#pragma endregion

        ICallable* replaceWithOneOrderHandlerStackDepthDeeper = new Callable();
        replaceWithOneOrderHandlerStackDepthDeeper->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#replaceWithOneOrderHandlerStackDepthDeeper should never be executed as it's Encounter() "
                    "function "
                    "should make another order the currentOrder",
                    Logger::ERROR);
            });
        replaceWithOneOrderHandlerStackDepthDeeper->SetEncounterFunction(
            []()
            {
                CodeGenerator.IncrementOrderHandlerStackDepth();
                Logger.Log("Replaced with: " + CodeGenerator.GetNextOrder().ToString(), Logger::DEBUG);
                CodeGenerator.DecreaseOrderHandlerStackDepth();
            });
        replaceWithOneOrderHandlerStackDepthDeeper->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("replaceWithOneOrderHandlerStackDepthDeeper",
                                     replaceWithOneOrderHandlerStackDepthDeeper);

        ICallable* escapedReplaceWithOneOrderHandlerStackDepthDeeper = new Callable();
        escapedReplaceWithOneOrderHandlerStackDepthDeeper->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#escapedReplaceWithOneOrderHandlerStackDepthDeeper should never be executed as it's Encounter() "
                    "function "
                    "should make #replaceWithOneOrderHandlerStackDepthDeeper the currentOrder",
                    Logger::ERROR);
            });
        escapedReplaceWithOneOrderHandlerStackDepthDeeper->SetEncounterFunction(
            []() {
                CodeGenerator.SetCurrentOrder(
                    Order("replaceWithOneOrderHandlerStackDepthDeeper", Order::CompilerInstruction));
            });
        escapedReplaceWithOneOrderHandlerStackDepthDeeper->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("escapedReplaceWithOneOrderHandlerStackDepthDeeper",
                                     escapedReplaceWithOneOrderHandlerStackDepthDeeper);

        ICallable* forceExecuteNextOrder = new Callable();
        forceExecuteNextOrder->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder(false);
                CodeGenerator.HandleOrder(nextOrder, false);
            });
        forceExecuteNextOrder->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("forceExecuteNextOrder", forceExecuteNextOrder);

        ICallable* executeNextInEncounterPhase = new Callable();
        executeNextInEncounterPhase->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#executeNextInEncounterPhase should never be executed as it's Encounter() "
                    "function "
                    "should make another order the currentOrder",
                    Logger::ERROR);
            });
        executeNextInEncounterPhase->SetEncounterFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();
                CodeGenerator.HandleOrder(nextOrder, false);
                CodeGenerator.GetNextOrder();  // As Order has been executed in Encounter, advance one more
            });
        CodeGenerator.AddInstruction("executeNextInEncounterPhase", executeNextInEncounterPhase);

        ICallable* forceExecuteNextOrderInEncounterPhase = new Callable();
        forceExecuteNextOrderInEncounterPhase->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#forceExecuteNextInEncounterPhase should never be executed as it's Encounter() "
                    "function "
                    "should make another order the currentOrder",
                    Logger::ERROR);
            });
        forceExecuteNextOrderInEncounterPhase->SetEncounterFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder(false);
                CodeGenerator.HandleOrder(nextOrder, false);
                CodeGenerator.GetNextOrder();  // As Order has been executed in Encounter, advance one more
            });
        forceExecuteNextOrderInEncounterPhase->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("forceExecuteNextOrderInEncounterPhase", forceExecuteNextOrderInEncounterPhase);

        ICallable* escapedForceExecuteNextOrderInEncounterPhase = new Callable();
        escapedForceExecuteNextOrderInEncounterPhase->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#escapedForceExecuteNextOrderInEncounterPhase should never be executed as it's Encounter() "
                    "function "
                    "should make #forceExecuteNextOrderInEncounterPhase the currentOrder",
                    Logger::ERROR);
            });
        escapedForceExecuteNextOrderInEncounterPhase->SetEncounterFunction(
            []() {
                CodeGenerator.SetCurrentOrder(
                    Order("forceExecuteNextOrderInEncounterPhase", Order::CompilerInstruction));
            });
        escapedForceExecuteNextOrderInEncounterPhase->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("escapedForceExecuteNextOrderInEncounterPhase",
                                     escapedForceExecuteNextOrderInEncounterPhase);

        ICallable* executeDirectCodeFromOrderQueueAsIdentifer = new Callable();
        executeDirectCodeFromOrderQueueAsIdentifer->SetExecuteFunction(
            []()
            {
                Order orderqueuePop = CodeGenerator.DequeueFromOrderQueue();

                if (orderqueuePop.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried executeDirectCodeFromOrderQueueAsIdentifer but next order " +
                                   orderqueuePop.GetName() + " is not direct code",
                               Logger::ERROR);
                    return;
                }

                Logger.Log("Executing direct code from order queue: " + orderqueuePop.GetName() + " as callable",
                           Logger::DEBUG);

                Order identiferOrder = Order(orderqueuePop.GetName(), Order::Identifier);

                ICallable* callable = CodeGenerator.GetCallable(identiferOrder);

                if (callable == nullptr)
                {
                    Logger.Log("No callable found for order: " + orderqueuePop.GetName(), Logger::ERROR);
                    return;
                }

                callable->Execute();
            });
        CodeGenerator.AddInstruction("executeDirectCodeFromOrderQueueAsIdentifer",
                                     executeDirectCodeFromOrderQueueAsIdentifer);

#pragma region New Orders

        ICallable* assignNextIdentifier = new Callable();
        assignNextIdentifier->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();

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
                callable->SetExecuteFunction([code]() { CodeGenerator.PutInFront(*code); });
                CodeGenerator.AddIdentifier(nextOrder.GetName(), callable);

                Logger.Log("New identifier code: \n" + code->ToString(), Logger::DEBUG);
            });
        CodeGenerator.AddInstruction("assignNextIdentifier", assignNextIdentifier);

        ICallable* assignNextIdentifierToOneOrder = new Callable();
        assignNextIdentifierToOneOrder->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();

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
                callable->SetExecuteFunction([code]() { CodeGenerator.PutInFront(code); });
                CodeGenerator.AddIdentifier(nextOrder.GetName(), callable);
            });
        CodeGenerator.AddInstruction("assignNextIdentifierToOneOrder", assignNextIdentifierToOneOrder);

        ICallable* makeNextOrderOrderQueueProof = new Callable();
        makeNextOrderOrderQueueProof->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();

                Logger.Log("Making next identifier order queue proof '" + nextOrder.ToString() + "'", Logger::DEBUG);

                ICallable* callable = CodeGenerator.GetCallable(nextOrder);

                if (callable == nullptr)
                {
                    Logger.Log(
                        "No callable found for order: " + nextOrder.GetName() + " in makeNextOrderOrderQueueProof",
                        Logger::ERROR);
                    return;
                }

                callable->SetOrderQueueProof(true);
            });
        CodeGenerator.AddInstruction("makeNextOrderOrderQueueProof", makeNextOrderOrderQueueProof);

        ICallable* makeNextOrderCommentProof = new Callable();
        makeNextOrderCommentProof->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();

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

#pragma endregion

#pragma region GeneratorVars

        // Expects generator var name as Dequeue of OrderQueue as DirectCode
        ICallable* getIntGeneratorVar = new Callable();
        getIntGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried getIntGeneratorVar but order from OrderQueue is not direct code", Logger::ERROR);
                    return;
                }

                std::string generatorVarName = nameOrder.GetName();
                int value = CodeGenerator.GetIntGeneratorVar(generatorVarName);
                CodeGenerator.PutInFront(Order(std::to_string(value), Order::DirectCode));
            });
        CodeGenerator.AddInstruction("getIntGeneratorVar", getIntGeneratorVar);

        // Expects generator var name first and value second as Dequeue of OrderQueue as DirectCode
        ICallable* setIntGeneratorVar = new Callable();
        setIntGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried setIntGeneratorVar but first order (name) from OrderQueue is not direct code",
                               Logger::ERROR);
                    return;
                }

                Order valueOrder = CodeGenerator.DequeueFromOrderQueue();
                if (valueOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried setIntGeneratorVar but second order (value) from OrderQueue is not direct code",
                               Logger::ERROR);
                    return;
                }

                std::string generatorVarName = nameOrder.GetName();
                int value = std::stoi(valueOrder.GetName());
                CodeGenerator.SetIntGeneratorVar(generatorVarName, value);
            });
        CodeGenerator.AddInstruction("setIntGeneratorVar", setIntGeneratorVar);

        // Expects generator var name first and change second as Dequeue of OrderQueue as DirectCode
        ICallable* changeIntGeneratorVar = new Callable();
        changeIntGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried changeIntGeneratorVar but first order (name) from OrderQueue is not direct code",
                               Logger::ERROR);
                    return;
                }

                Order changeOrder = CodeGenerator.DequeueFromOrderQueue();
                if (changeOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log(
                        "Tried changeIntGeneratorVar but second order (change) from OrderQueue is not direct code",
                        Logger::ERROR);
                    return;
                }

                std::string generatorVarName = nameOrder.GetName();
                int change = std::stoi(changeOrder.GetName());

                int value = CodeGenerator.GetIntGeneratorVar(generatorVarName);
                value += change;

                CodeGenerator.SetIntGeneratorVar(generatorVarName, value);
            });
        CodeGenerator.AddInstruction("changeIntGeneratorVar", changeIntGeneratorVar);

        // Expects generator var name as Dequeue of OrderQueue as DirectCode
        ICallable* getStringGeneratorVar = new Callable();
        getStringGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried getStringGeneratorVar but order from OrderQueue is not direct code",
                               Logger::ERROR);
                    return;
                }

                std::string generatorVarName = nameOrder.GetName();
                std::string value = CodeGenerator.GetStringGeneratorVar(generatorVarName);
                CodeGenerator.PutInFront(Order(value, Order::DirectCode));
            });
        CodeGenerator.AddInstruction("getStringGeneratorVar", getStringGeneratorVar);

        // Expects generator var name first and value second as Dequeue of OrderQueue as DirectCode
        ICallable* setStringGeneratorVar = new Callable();
        setStringGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log("Tried setStringGeneratorVar but first order (name) from OrderQueue is not direct code",
                               Logger::ERROR);
                    return;
                }

                Order valueOrder = CodeGenerator.DequeueFromOrderQueue();
                if (valueOrder.GetType() != Order::DirectCode)
                {
                    Logger.Log(
                        "Tried setStringGeneratorVar but second order (value) from OrderQueue is not direct code",
                        Logger::ERROR);
                    return;
                }

                std::string generatorVarName = nameOrder.GetName();
                std::string value = valueOrder.GetName();
                CodeGenerator.SetStringGeneratorVar(generatorVarName, value);
            });
        CodeGenerator.AddInstruction("setStringGeneratorVar", setStringGeneratorVar);

#pragma endregion

        ICallable* putInFrontNextOrderAsDirectCode = new Callable();
        putInFrontNextOrderAsDirectCode->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();
                Order directCode = Order(nextOrder.GetName(), Order::DirectCode);
                CodeGenerator.PutInFront(directCode);
            });
        CodeGenerator.AddInstruction("putInFrontNextOrderAsDirectCode", putInFrontNextOrderAsDirectCode);

#pragma region Debug

        ICallable* debug = new Callable();
        debug->SetExecuteFunction([]() { Logger.Log("DEBUG PRINT", Logger::DEBUG); });
        CodeGenerator.AddInstruction("debug", debug);

        ICallable* debugStatus = new Callable();
        debugStatus->SetExecuteFunction(
            []()
            {
                Logger.Log("---DEBUG STATUS", Logger::DEBUG);
                Logger.Log("---Current order: " + CodeGenerator.GetCurrentOrder().ToString(), Logger::DEBUG);
                Logger.Log("---Current mode: " + std::to_string(CodeGenerator.GetCurrentMode()), Logger::DEBUG);
            });
        CodeGenerator.AddInstruction("debugStatus", debugStatus);

        ICallable* activateDebugMode = new Callable();
        activateDebugMode->SetExecuteFunction([]() { Logger.SetDebug(true); });
        CodeGenerator.AddInstruction("activateDebugMode", activateDebugMode);

        ICallable* deactivateDebugMode = new Callable();
        deactivateDebugMode->SetExecuteFunction([]() { Logger.SetDebug(false); });
        CodeGenerator.AddInstruction("deactivateDebugMode", deactivateDebugMode);

#pragma endregion
    }
};