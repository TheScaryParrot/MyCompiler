#pragma once

#include <vector>

#include "../../utils/Logger.cpp"
#include "../AbstractGenerator.cpp"
#include "../instructions/InstructionHandler.cpp"
#include "IOrderFetcher.cpp"

class FetchHandler
{
   public:
    void Fetch(AbstractGenerator* generator)
    {
        if (fetcherDepth >= fetcherQueue.size())
        {
            Logger.Log("FetchDepth is greater than fetcherQueue size", Logger::ERROR);
            generator->SetCurrentOrder(Order::Empty());
            return;
        }

        auto queueIterator = fetcherQueue.begin() + fetcherDepth;
        IOrderFetcher* fetcher = *queueIterator;
        Order order = fetcher->Next();

        if (fetcher->IsEmpty())
        {
            fetcherQueue.erase(queueIterator);

            if (fetcher != nullptr) delete fetcher;
        }

        /*if (order.GetType() == Order::Instruction)
        {
            Instruction* instruction = InstructionHandler.GetInstruction(order.GetName());
            if (instruction != nullptr) instruction->Fetch(generator, order);
        }*/

        generator->SetCurrentOrder(order);
        generator->IncrementPhase();
        return;
    }

    void IncrementFetcherDepth()
    {
        Logger.Log("Incrementing fetcher depth", Logger::DEBUG);
        fetcherDepth++;
    }

    void DecrementFetcherDepth()
    {
        Logger.Log("Decrementing fetcher depth", Logger::DEBUG);
        fetcherDepth--;
    }

    void PutInFront(IOrderFetcher* fetcher)
    {
        if (fetcher->IsEmpty()) return;

        fetcherQueue.insert(fetcherQueue.begin() + fetcherDepth, fetcher);
    }

    bool IsDone() { return fetcherQueue.empty(); }

   private:
    unsigned int fetcherDepth = 0;
    std::vector<IOrderFetcher*> fetcherQueue;
};