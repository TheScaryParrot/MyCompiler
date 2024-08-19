#pragma once

#include "../OrderQueue.cpp"
#include "IOrderFetcher.cpp"

class OrderQueueFetcher : public IOrderFetcher
{
   public:
    OrderQueueFetcher(OrderQueue* queue) : queue(queue) {}

    virtual Order Next() override { return queue->Dequeue(); }

    virtual bool IsEmpty() override { return queue->IsEmpty(); }

   private:
    OrderQueue* queue;
};