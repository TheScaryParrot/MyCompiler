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

    Order DequeueOrder()
    {
        Order order = orderQueueStack.Top()->Dequeue();

        if (orderQueueStack.Top()->IsEmpty())
        {
            delete orderQueueStack.Pop();
        }

        return order;
    }
    OrderQueue* PopOrderQueue() { return orderQueueStack.Pop(); }

    void ClearAllOrderQueues() { orderQueueStack = Stack<OrderQueue*>(); }

   private:
    Stack<OrderQueue*> orderQueueStack = Stack<OrderQueue*>();
};