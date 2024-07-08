#pragma once

#include "../utils/Stack.cpp"
#include "OrderQueue.cpp"

class OrderQueueStackHandler
{
   public:
    void PushNewOrderQueue();
    void EnqueueOrder(Order order);

    Order DequeueOrder();
    OrderQueue* PopOrderQueue();

    void ClearAllOrderQueues();

   private:
    Stack<OrderQueue*> orderQueueStack = Stack<OrderQueue*>();
};

void OrderQueueStackHandler::PushNewOrderQueue() { orderQueueStack.Push(new OrderQueue()); }

void OrderQueueStackHandler::EnqueueOrder(Order order)
{
    if (orderQueueStack.IsEmpty())
    {
        PushNewOrderQueue();
    }

    orderQueueStack.Top()->Enqueue(order);
}

Order OrderQueueStackHandler::DequeueOrder() { return orderQueueStack.Top()->Dequeue(); }

OrderQueue* OrderQueueStackHandler::PopOrderQueue() { return orderQueueStack.Pop(); }

void OrderQueueStackHandler::ClearAllOrderQueues() { orderQueueStack = Stack<OrderQueue*>(); }