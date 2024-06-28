#pragma once

#include "../Order.cpp"
#include "../utils/Queue.cpp"

class OrderQueue
{
   public:
    OrderQueue();

    void Enqueue(Order order);
    Order Dequeue();
    Order Front();
    bool IsEmpty();
    void Clear();

   private:
    Queue<Order> queue;
};

OrderQueue::OrderQueue() {}

void OrderQueue::Enqueue(Order order) { this->queue.Enqueue(order); }

Order OrderQueue::Dequeue() { return this->queue.Dequeue(); }

Order OrderQueue::Front() { return this->queue.Front(); }

bool OrderQueue::IsEmpty() { return this->queue.IsEmpty(); }

void OrderQueue::Clear() { this->queue.Clear(); }