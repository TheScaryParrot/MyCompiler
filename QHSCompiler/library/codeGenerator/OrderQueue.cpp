#pragma once

#include "../Order.cpp"
#include "../utils/Queue.cpp"

class OrderQueue
{
   public:
    void Enqueue(Order order) { this->queue.Enqueue(order); }
    Order Dequeue() { return this->queue.Dequeue(); }
    Order Front() { return this->queue.Front(); }
    bool IsEmpty() { return this->queue.IsEmpty(); }
    void Clear() { this->queue.Clear(); }

   private:
    Queue<Order> queue;
};