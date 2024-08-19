#pragma once

#include <vector>

#include "../../Order.cpp"
#include "../../utils/Logger.cpp"
#include "IOrderFetcher.cpp"

class FetchHandler
{
   public:
    Order Fetch()
    {
        if (fetcherDepth >= fetcherQueue.size())
        {
            Logger.Log("FetchDepth is greater than fetcherQueue size", Logger::ERROR);
            return Order::Empty();
        }

        auto queueIterator = fetcherQueue.begin() + fetcherDepth;
        IOrderFetcher* fetcher = *queueIterator;
        Order order = fetcher->Next();

        if (fetcher->IsEmpty())
        {
            fetcherQueue.erase(queueIterator);

            if (fetcher != nullptr) delete fetcher;
        }

        return order;
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
        if (fetcher->IsEmpty())
        {
            return;
        }

        fetcherQueue.insert(fetcherQueue.begin() + fetcherDepth, fetcher);
    }

    bool IsDone() { return fetcherQueue.empty(); }

   private:
    unsigned int fetcherDepth = 0;
    std::vector<IOrderFetcher*> fetcherQueue;
};