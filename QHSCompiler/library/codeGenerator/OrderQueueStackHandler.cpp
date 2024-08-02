#pragma once

#include "../utils/Stack.cpp"
#include "OrderQueue.cpp"

class OrderQueueStackHandler
{
   public:
    void PushNewOrderQueue() { orderQueueStack.Push(new OrderQueue()); }
    void EnqueueOrder(Order order)
    {
        if (orderQueueStack.IsEmpty())
        {
            PushNewOrderQueue();
        }

        orderQueueStack.Top()->Enqueue(order);
    }

    Order DequeueOrder() { return orderQueueStack.Top()->Dequeue(); }
    OrderQueue* PopOrderQueue() { return orderQueueStack.Pop(); }

    void ClearAllOrderQueues() { orderQueueStack = Stack<OrderQueue*>(); }

   private:
    Stack<OrderQueue*> orderQueueStack = Stack<OrderQueue*>();
};