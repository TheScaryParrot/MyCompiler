#pragma once

#include "../InputFile.cpp"
#include "AbstractGenerator.cpp"
#include "decode/DecodeHandler.cpp"
#include "execute/ExecuteHandler.cpp"
#include "fetch/FetchHandler.cpp"
#include "fetch/InputFileFetcher.cpp"
#include "fetch/OrderQueueFetcher.cpp"

class Generator : public AbstractGenerator
{
   public:
    Generator(InputFile* file) { this->fetchHandler.PutInFront(new InputFileFetcher(file)); }

    AssemblyCode* Generate()
    {
        unsigned int phaseCounter = 0;

        while (!fetchHandler.IsDone() && phaseCounter < 100000)
        {
            ExecuteCurrentPhase();
            phaseCounter++;
        }

        if (phaseCounter >= 100000)
        {
            Logger.Log("Generator reached phase limit of 100000", Logger::ERROR);
            Logger.Log("Final phase was " + std::to_string(GetCurrentPhase()), Logger::ERROR);
        }

        return this->assemblyCode;
    }

    virtual void ExecuteCurrentPhase()
    {
        switch (this->GetCurrentPhase())
        {
            case GeneratorPhases::FETCH:
                fetchHandler.Fetch(this);
                break;
            case GeneratorPhases::DECODE:
                decodeHandler.Decode(this);
                break;
            case GeneratorPhases::EXECUTE:
                executeHandler.Execute(this);
                break;
            default:
                Logger.Log("Generator doesn't know what to do with GeneratorPhase at index: " +
                               std::to_string(GetCurrentPhase()) + ". Setting phase to FETCH",
                           Logger.ERROR);
                SetCurrentPhase(GeneratorPhases::FETCH);
                break;
        }
    }

    virtual void IncrementFetchDepth() override { fetchHandler.IncrementFetcherDepth(); }
    virtual void DecrementFetchDepth() override { fetchHandler.DecrementFetcherDepth(); }

    virtual void EnterComment() override { decodeHandler.EnterComment(); }
    virtual void ExitComment() override { decodeHandler.ExitComment(); }
    virtual void IncrementOrderQueueDepth() override { decodeHandler.IncrementOrderQueueDepthCounter(); }
    virtual void DecrementOrderQueueDepth() override { decodeHandler.DecrementOrderQueueDepthCounter(); }
    virtual bool IsOrderQueueActive() override { return decodeHandler.IsOrderQueueActive(); }

    virtual void PutInFront(Order order) override
    {
        fetchHandler.PutInFront(new OrderQueueFetcher(new OrderQueue(order)));
    }
    virtual void PutInFront(OrderQueue orderQueue) override
    {
        fetchHandler.PutInFront(new OrderQueueFetcher(new OrderQueue(orderQueue)));
    }

    virtual Order DequeueFromOrderQueue() override { return decodeHandler.DequeueFromOrderQueue(); }
    virtual void EnqueueInOrderQueue(Order order) override { decodeHandler.EnqueueInOrderQueue(order); }
    virtual void EnqueueInOrderQueueFront(Order order) override { decodeHandler.EnqueueInOrderQueueFront(order); }
    virtual OrderQueue GetOrderQueueCopy() override { return decodeHandler.GetOrderQueueCopy(); }
    virtual OrderQueue* DequeueWholeOrderQueue() override { return decodeHandler.DequeueWholeOrderQueue(); }

   private:
    FetchHandler fetchHandler = FetchHandler();
    DecodeHandler decodeHandler = DecodeHandler();
    ExecuteHandler executeHandler = ExecuteHandler();

    /*void InitInstructions()
    {

#pragma region OrderQueue


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
                    "#replaceWithOneOrderHandlerStackDepthDeeper should never be executed as it's
Encounter() " "function " "should make another order the currentOrder", Logger::ERROR);
            });
        replaceWithOneOrderHandlerStackDepthDeeper->SetEncounterFunction(
            []()
            {
                CodeGenerator.IncrementFetchDepth();
                Logger.Log("Replaced with: " + CodeGenerator.GetNextOrder().ToString(), Logger::DEBUG);
                CodeGenerator.DecrementFetchDepth();
            });
        replaceWithOneOrderHandlerStackDepthDeeper->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("replaceWithOneOrderHandlerStackDepthDeeper",
                                     replaceWithOneOrderHandlerStackDepthDeeper);

        ICallable* escapedReplaceWithOneOrderHandlerStackDepthDeeper = new Callable();
        escapedReplaceWithOneOrderHandlerStackDepthDeeper->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#escapedReplaceWithOneOrderHandlerStackDepthDeeper should never be executed as it's
Encounter() " "function " "should make #replaceWithOneOrderHandlerStackDepthDeeper the currentOrder",
                    Logger::ERROR);
            });
        escapedReplaceWithOneOrderHandlerStackDepthDeeper->SetEncounterFunction(
            []() {
                CodeGenerator.SetCurrentOrder(
                    Order("replaceWithOneOrderHandlerStackDepthDeeper", Order::Instruction));
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
                CodeGenerator.GetNextOrder();  // As Order has been executed in Encounter, advance one
more
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
                CodeGenerator.GetNextOrder();  // As Order has been executed in Encounter, advance one
more
            });
        forceExecuteNextOrderInEncounterPhase->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("forceExecuteNextOrderInEncounterPhase",
forceExecuteNextOrderInEncounterPhase);

        ICallable* escapedForceExecuteNextOrderInEncounterPhase = new Callable();
        escapedForceExecuteNextOrderInEncounterPhase->SetExecuteFunction(
            []()
            {
                Logger.Log(
                    "#escapedForceExecuteNextOrderInEncounterPhase should never be executed as it's
Encounter() " "function " "should make #forceExecuteNextOrderInEncounterPhase the currentOrder",
                    Logger::ERROR);
            });
        escapedForceExecuteNextOrderInEncounterPhase->SetEncounterFunction(
            []() {
                CodeGenerator.SetCurrentOrder(
                    Order("forceExecuteNextOrderInEncounterPhase", Order::Instruction));
            });
        escapedForceExecuteNextOrderInEncounterPhase->SetOrderQueueProof(true);
        CodeGenerator.AddInstruction("escapedForceExecuteNextOrderInEncounterPhase",
                                     escapedForceExecuteNextOrderInEncounterPhase);

        ICallable* executeDirectCodeFromOrderQueueAsIdentifer = new Callable();
        executeDirectCodeFromOrderQueueAsIdentifer->SetExecuteFunction(
            []()
            {
                Order orderqueuePop = CodeGenerator.DequeueFromOrderQueue();

                if (orderqueuePop.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried executeDirectCodeFromOrderQueueAsIdentifer but next order " +
                                   orderqueuePop.GetName() + " is not direct code",
                               Logger::ERROR);
                    return;
                }

                Logger.Log("Executing direct code from order queue: " + orderqueuePop.GetName() + " as
callable", Logger::DEBUG);

                Order identiferOrder = Order(orderqueuePop.GetName(), Order::Identifier);

                ICallable* callable = CodeGenerator.GetCallable(identiferOrder);

                if (callable == nullptr)
                {
                    Logger.Log("No callable found for order: " + orderqueuePop.GetName(),
Logger::ERROR); return;
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
                    Logger.Log("Tried assigning next identifier but next order is not identifier.
Skipping assign", Logger::ERROR);

                    return;
                }

                Logger.Log("Assigning next order '" + nextOrder.ToString() + "'", Logger::DEBUG);

                OrderQueue* code = CodeGenerator.PopOrderQueue();

                if (code == nullptr)
                {
                    Logger.Log("No code found for assign next identifier '" + nextOrder.ToString() +
"'", Logger::ERROR); return;
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
                    Logger.Log("Tried assigning next identifier but next order is not identifier .
Skipping assign", Logger::ERROR);

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

                Logger.Log("Making next identifier order queue proof '" + nextOrder.ToString() + "'",
Logger::DEBUG);

                ICallable* callable = CodeGenerator.GetCallable(nextOrder);

                if (callable == nullptr)
                {
                    Logger.Log(
                        "No callable found for order: " + nextOrder.GetName() + " in
makeNextOrderOrderQueueProof", Logger::ERROR); return;
                }

                callable->SetOrderQueueProof(true);
            });
        CodeGenerator.AddInstruction("makeNextOrderOrderQueueProof", makeNextOrderOrderQueueProof);

        ICallable* makeNextOrderCommentProof = new Callable();
        makeNextOrderCommentProof->SetExecuteFunction(
            []()
            {
                Order nextOrder = CodeGenerator.GetNextOrder();

                Logger.Log("Making next identifier comment proof '" + nextOrder.ToString() + "'",
Logger::DEBUG);

                ICallable* callable = CodeGenerator.GetCallable(nextOrder);

                if (callable == nullptr)
                {
                    Logger.Log("No callable found for order: " + nextOrder.GetName() + " in
makeNextOrderCommentProof", Logger::ERROR); return;
                }

                callable->SetCommentProof(true);
            });
        CodeGenerator.AddInstruction("makeNextOrderCommentProof", makeNextOrderCommentProof);

#pragma endregion

#pragma region GeneratorVars

        // Expects generator var name as Dequeue of OrderQueue as LiteralCode
        ICallable* getIntGeneratorVar = new Callable();
        getIntGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried getIntGeneratorVar but order from OrderQueue is not direct code",
Logger::ERROR); return;
                }

                std::string generatorVarName = nameOrder.GetName();
                int value = CodeGenerator.GetIntGeneratorVar(generatorVarName);
                CodeGenerator.PutInFront(Order(std::to_string(value), Order::LiteralCode));
            });
        CodeGenerator.AddInstruction("getIntGeneratorVar", getIntGeneratorVar);

        // Expects generator var name first and value second as Dequeue of OrderQueue as LiteralCode
        ICallable* setIntGeneratorVar = new Callable();
        setIntGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried setIntGeneratorVar but first order (name) from OrderQueue is not
direct code", Logger::ERROR); return;
                }

                Order valueOrder = CodeGenerator.DequeueFromOrderQueue();
                if (valueOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried setIntGeneratorVar but second order (value) from OrderQueue is not
direct code", Logger::ERROR); return;
                }

                std::string generatorVarName = nameOrder.GetName();
                int value = std::stoi(valueOrder.GetName());
                CodeGenerator.SetIntGeneratorVar(generatorVarName, value);
            });
        CodeGenerator.AddInstruction("setIntGeneratorVar", setIntGeneratorVar);

        // Expects generator var name first and change second as Dequeue of OrderQueue as LiteralCode
        ICallable* changeIntGeneratorVar = new Callable();
        changeIntGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried changeIntGeneratorVar but first order (name) from OrderQueue is
not direct code", Logger::ERROR); return;
                }

                Order changeOrder = CodeGenerator.DequeueFromOrderQueue();
                if (changeOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log(
                        "Tried changeIntGeneratorVar but second order (change) from OrderQueue is not
direct code", Logger::ERROR); return;
                }

                std::string generatorVarName = nameOrder.GetName();
                int change = std::stoi(changeOrder.GetName());

                int value = CodeGenerator.GetIntGeneratorVar(generatorVarName);
                value += change;

                CodeGenerator.SetIntGeneratorVar(generatorVarName, value);
            });
        CodeGenerator.AddInstruction("changeIntGeneratorVar", changeIntGeneratorVar);

        // Expects generator var name as Dequeue of OrderQueue as LiteralCode
        ICallable* getStringGeneratorVar = new Callable();
        getStringGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried getStringGeneratorVar but order from OrderQueue is not direct
code", Logger::ERROR); return;
                }

                std::string generatorVarName = nameOrder.GetName();
                std::string value = CodeGenerator.GetStringGeneratorVar(generatorVarName);
                CodeGenerator.PutInFront(Order(value, Order::LiteralCode));
            });
        CodeGenerator.AddInstruction("getStringGeneratorVar", getStringGeneratorVar);

        // Expects generator var name first and value second as Dequeue of OrderQueue as LiteralCode
        ICallable* setStringGeneratorVar = new Callable();
        setStringGeneratorVar->SetExecuteFunction(
            []()
            {
                Order nameOrder = CodeGenerator.DequeueFromOrderQueue();
                if (nameOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log("Tried setStringGeneratorVar but first order (name) from OrderQueue is
not direct code", Logger::ERROR); return;
                }

                Order valueOrder = CodeGenerator.DequeueFromOrderQueue();
                if (valueOrder.GetType() != Order::LiteralCode)
                {
                    Logger.Log(
                        "Tried setStringGeneratorVar but second order (value) from OrderQueue is not
direct code", Logger::ERROR); return;
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
                Order directCode = Order(nextOrder.GetName(), Order::LiteralCode);
                CodeGenerator.PutInFront(directCode);
            });
        CodeGenerator.AddInstruction("putInFrontNextOrderAsDirectCode",
putInFrontNextOrderAsDirectCode);

#pragma region Debug

        ICallable* debug = new Callable();
        debug->SetExecuteFunction([]() { Logger.Log("DEBUG PRINT", Logger::DEBUG); });
        CodeGenerator.AddInstruction("debug", debug);

        ICallable* debugStatus = new Callable();
        debugStatus->SetExecuteFunction(
            []()
            {
                Logger.Log("---DEBUG STATUS", Logger::DEBUG);
                Logger.Log("---Current order: " + CodeGenerator.GetCurrentOrder().ToString(),
Logger::DEBUG); Logger.Log("---Current mode: " + std::to_string(CodeGenerator.GetCurrentMode()),
Logger::DEBUG);
            });
        CodeGenerator.AddInstruction("debugStatus", debugStatus);

        ICallable* activateDebugMode = new Callable();
        activateDebugMode->SetExecuteFunction([]() { Logger.SetDebug(true); });
        CodeGenerator.AddInstruction("activateDebugMode", activateDebugMode);

        ICallable* deactivateDebugMode = new Callable();
        deactivateDebugMode->SetExecuteFunction([]() { Logger.SetDebug(false); });
        CodeGenerator.AddInstruction("deactivateDebugMode", deactivateDebugMode);

#pragma endregion
    }*/
};