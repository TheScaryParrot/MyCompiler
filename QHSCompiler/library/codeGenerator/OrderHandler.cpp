#pragma once

#include <memory>

#include "../InputFile.cpp"
#include "../Order.cpp"
#include "../scanner/Scanner.cpp"
#include "../utils/Queue.cpp"
#include "../utils/Stack.cpp"
#include "OrderQueue.cpp"

class OrderHandler
{
   public:
    OrderHandler() = default;
    OrderHandler(InputFile* file) { this->file = file; }

    Order GetCurrentOrder() { return currentOrder; }

    /// @brief Advances next order; order can be retrieved from GetCurrentOrder()
    void NextOrder()
    {
        if (stackedOrderQueues.IsEmpty())
        {
            currentOrder = scanner.ScanOrder(file);
            return;
        }

        OrderQueue* queue = stackedOrderQueues.Top();
        Order order = queue->Dequeue();

        if (queue->IsEmpty())
        {
            delete stackedOrderQueues.Pop();
        }

        currentOrder = order;
    }

    void PutInFront(Order order)
    {
        OrderQueue* newQueue = new OrderQueue();
        newQueue->Enqueue(order);

        stackedOrderQueues.Push(newQueue);
    }
    void PutInFront(OrderQueue queue)
    {
        if (queue.IsEmpty())
        {
            return;
        }

        OrderQueue* newQueue = new OrderQueue(queue);

        stackedOrderQueues.Push(newQueue);
    }

    bool IsDone() { return stackedOrderQueues.IsEmpty() && file->IsEndOfFile(); }

   private:
    Order currentOrder = Order::Empty();

    Scanner scanner;
    InputFile* file;

    Stack<OrderQueue*> stackedOrderQueues;
};
