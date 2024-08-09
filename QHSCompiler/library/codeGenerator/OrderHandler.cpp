#pragma once

#include <memory>

#include "../InputFile.cpp"
#include "../Order.cpp"
#include "../scanner/Scanner.cpp"
#include "../utils/Logger.cpp"
#include "../utils/Queue.cpp"
#include "../utils/Stack.cpp"
#include "OrderQueue.cpp"

class OrderHandler
{
   public:
    OrderHandler(InputFile* file) { this->scanner = new Scanner(file); }
    ~OrderHandler() { delete scanner; }

    /// @brief Advances next order; order can be retrieved from GetCurrentOrder()
    Order GetNextOrder()
    {
        if (orderStackDepth >= orderQueues.size())
        {
            return scanner->ScanOrder();
        }

        auto queueIterator = orderQueues.begin() + orderStackDepth;
        OrderQueue* queue = *queueIterator;
        Order order = queue->Dequeue();

        if (queue->IsEmpty())
        {
            orderQueues.erase(queueIterator);

            if (queue != nullptr) delete queue;
        }

        return order;
    }

    void IncrementOrderStackDepth()
    {
        Logger.Log("Incrementing order stack depth", Logger::DEBUG);
        orderStackDepth++;
    }

    void DecreaseOrderStackDepth()
    {
        Logger.Log("Decrementing order stack depth", Logger::DEBUG);
        orderStackDepth--;
    }

    void PutInFront(Order order)
    {
        OrderQueue* newQueue = new OrderQueue();
        newQueue->Enqueue(order);

        orderQueues.insert(orderQueues.begin() + orderStackDepth, newQueue);
    }
    void PutInFront(OrderQueue queue)
    {
        if (queue.IsEmpty())
        {
            return;
        }

        OrderQueue* newQueue = new OrderQueue(queue);

        orderQueues.insert(orderQueues.begin() + orderStackDepth, newQueue);
    }

    bool IsDone() { return orderQueues.empty() && scanner->IsDone(); }

   private:
    Scanner* scanner;

    unsigned int orderStackDepth = 0;

    std::vector<OrderQueue*> orderQueues;
};
