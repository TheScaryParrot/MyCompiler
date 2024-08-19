#pragma once

#include <iostream>
#include <string>

#include "../assembly/AssemblyCode.cpp"
#include "../utils/Logger.cpp"
#include "../utils/Map.cpp"
#include "Environment.cpp"
#include "OrderQueueStackHandler.cpp"
#include "fetch/FetchHandler.cpp"
#include "fetch/InputFileFetcher.cpp"
#include "fetch/OrderQueueFetcher.cpp"

static class CodeGenerator
{
   public:
    void Init(InputFile* file, AssemblyCode* assemblyCode)
    {
        this->fetchHandler = new FetchHandler();
        this->fetchHandler->PutInFront(new InputFileFetcher(file));
        this->assemblyCode = assemblyCode;
    }
    ~CodeGenerator() { delete fetchHandler; }

    enum EModes
    {
        EXECUTE,
        ORDER_QUEUE,
        COMMENT
    };

    bool IsDone() { return fetchHandler->IsDone(); }
    Order GetNextOrder(bool checkForMode = true)
    {
        Order newOrder = fetchHandler->Fetch();
        currentOrder = newOrder;

        // If the order has a callable and is not in OrderQueue or Comment, call ICallable::Encounter()
        if (newOrder.GetType() == Order::EOrderTypes::DirectCode) return currentOrder;

        ICallable* callable = GetCallable(newOrder);
        if (callable == nullptr) return currentOrder;

        if (IsInMode(EModes::COMMENT) && checkForMode && !callable->IsCommentProof()) return currentOrder;
        if (IsInMode(EModes::ORDER_QUEUE) && checkForMode && !callable->IsOrderQueueProof()) return currentOrder;

        callable->Encounter();
        return currentOrder;
    }
    Order GetCurrentOrder() { return currentOrder; }
    void SetCurrentOrder(Order order) { currentOrder = order; }
    void IncrementFetchDepth() { fetchHandler->IncrementFetcherDepth(); }
    void DecrementFetchDepth() { fetchHandler->DecrementFetcherDepth(); }

    void HandleOrder(Order order, bool checkForMode)
    {
        if (order.GetType() == Order::EOrderTypes::DirectCode)
        {
            HandleDirectCode(order, checkForMode);
            return;
        }

        ICallable* callable = GetCallable(order);

        if (callable == nullptr)
        {
            if (IsInMode(EModes::COMMENT) && checkForMode)
            {
                return;
            }

            if (IsInMode(EModes::ORDER_QUEUE) && checkForMode)
            {
                EnqueueInOrderQueue(order);
                return;
            }

            Logger.Log("No callable found for order: " + order.GetName(), Logger::ERROR);

            return;
        }

        if (IsInMode(EModes::COMMENT) && checkForMode && !callable->IsCommentProof())
        {
            return;
        }

        if (IsInMode(EModes::ORDER_QUEUE) && checkForMode && !callable->IsOrderQueueProof())
        {
            EnqueueInOrderQueue(order);
            return;
        }

        callable->Execute();
    }

    void HandleDirectCode(Order order, bool checkForMode)
    {
        if (IsInMode(EModes::ORDER_QUEUE) && checkForMode)
        {
            EnqueueInOrderQueue(order);
            return;
        }

        if (IsInMode(EModes::COMMENT) && checkForMode)
        {
            return;
        }

        this->assemblyCode->AddCode(order.GetName());
    }

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

    void PutInFront(Order order)
    {
        OrderQueueFetcher* fetcher = new OrderQueueFetcher(new OrderQueue(order));
        fetchHandler->PutInFront(fetcher);
    }

    void PutInFront(OrderQueue orderQueue)
    {
        OrderQueueFetcher* fetcher = new OrderQueueFetcher(new OrderQueue(orderQueue));
        fetchHandler->PutInFront(fetcher);
    }

    void IncrementOrderQueueMode()
    {
        orderQueueDepthCounter++;

        if (orderQueueDepthCounter >= 1 && !IsInMode(EModes::ORDER_QUEUE))
        {
            PushMode(EModes::ORDER_QUEUE);
        }
    }
    void DecrementOrderQueueMode()
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
    void PutInFrontFromOrderQueue() { this->PutInFront(orderQueueStack.DequeueOrder()); }

    void AddInstruction(std::string name, ICallable* instruction)
    {
        instructionEnvironment.AddCallable(name, instruction);
    }
    void AddIdentifier(std::string name, ICallable* identifier) { identifierEnvironment.AddCallable(name, identifier); }

    int GetIntGeneratorVar(std::string name)
    {
        if (!intGeneratorVars.Contains(name))
        {
            Logger.Log("No int generator variable found with name: " + name, Logger::ERROR);
            return 0;
        }

        return intGeneratorVars.Get(name);
    }
    void SetIntGeneratorVar(std::string name, int value) { intGeneratorVars.Set(name, value); }

    std::string GetStringGeneratorVar(std::string name)
    {
        if (!stringGeneratorVars.Contains(name))
        {
            Logger.Log("No string generator variable found with name: " + name, Logger::ERROR);
            return "";
        }

        return stringGeneratorVars.Get(name);
    }
    void SetStringGeneratorVar(std::string name, std::string value) { stringGeneratorVars.Set(name, value); }

   private:
    AssemblyCode* assemblyCode;

    Stack<EModes> modeStack = Stack<EModes>();

    unsigned int orderQueueDepthCounter = 0;
    OrderQueueStackHandler orderQueueStack = OrderQueueStackHandler();

    Environment identifierEnvironment = Environment();
    Environment instructionEnvironment = Environment();

    FetchHandler* fetchHandler;
    Order currentOrder = Order::Empty();

    Map<std::string, int> intGeneratorVars;
    Map<std::string, std::string> stringGeneratorVars;

} CodeGenerator;
