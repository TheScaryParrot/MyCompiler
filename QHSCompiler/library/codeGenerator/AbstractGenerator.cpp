#pragma once

#include "../utils/Logger.cpp"
#include "../utils/Map.cpp"
#include "AssemblyCode.cpp"
#include "Order.cpp"
#include "OrderQueue.cpp"

enum GeneratorPhases
{
    FETCH,
    DECODE,
    EXECUTE,
    MAX  // Used in increment operator to return to first element upon reaching
};

// Prefix ++
GeneratorPhases& operator++(GeneratorPhases& phase)
{
    if (phase == MAX - 1)
    {
        phase = static_cast<GeneratorPhases>(0);
        return phase;
    }

    phase = static_cast<GeneratorPhases>(phase + 1);
    return phase;
}

/* Postfix ++ isn't needed
GeneratorPhases operator++(GeneratorPhases& phase, int)
{
    GeneratorPhases tmp = phase;
    ++phase;
    return tmp;
}*/

class AbstractGenerator
{
   public:
    void SetCurrentPhase(GeneratorPhases phase) { currentPhase = phase; }
    GeneratorPhases GetCurrentPhase() { return currentPhase; }
    void RestartCycle() { currentPhase = static_cast<GeneratorPhases>(0); }
    void IncrementPhase() { ++currentPhase; }
    virtual void ExecuteCurrentPhase() = 0;

    void SetCurrentOrder(Order order) { this->currentOrder = order; }
    Order GetCurrentOrder() { return this->currentOrder; }

    virtual void IncrementFetchDepth() = 0;
    virtual void DecrementFetchDepth() = 0;

    virtual void EnterComment() = 0;
    virtual void ExitComment() = 0;
    virtual void IncrementOrderQueueDepth() = 0;
    virtual void DecrementOrderQueueDepth() = 0;
    virtual bool IsOrderQueueActive() = 0;

    virtual void PutInFront(Order order) = 0;
    virtual void PutInFront(OrderQueue orderQueue) = 0;

    virtual Order DequeueFromOrderQueue() = 0;
    virtual void EnqueueInOrderQueue(Order order) = 0;
    virtual void EnqueueInOrderQueueFront(Order order) = 0;
    virtual OrderQueue GetOrderQueueCopy() = 0;
    virtual OrderQueue* DequeueWholeOrderQueue() = 0;

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

    AssemblyCode* assemblyCode = new AssemblyCode();

    void AddToAssemblyCode(std::string code) { this->assemblyCode->AddCode(code); }

   private:
    GeneratorPhases currentPhase = static_cast<GeneratorPhases>(0);

    Order currentOrder = Order::Empty();

    Map<std::string, int> intGeneratorVars;
    Map<std::string, std::string> stringGeneratorVars;
};