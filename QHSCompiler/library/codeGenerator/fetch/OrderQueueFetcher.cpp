#pragma once

#include "../OrderQueue.cpp"
#include "IOrderFetcher.cpp"

class OrderQueueFetcher : public IOrderFetcher
{
   public:
    OrderQueueFetcher(OrderQueue* queue) : queue(queue) {}

    virtual Order Next() override
    {
        Order order = queue->Dequeue();
        lastOrder = order;
        return order;
    }

    virtual bool IsEmpty() override { return queue->IsEmpty(); }

    virtual std::string GetLastOrderLog() override { return lastOrder.ToLogString(); }

   private:
    OrderQueue* queue;

    Order lastOrder = Order::Empty();
};