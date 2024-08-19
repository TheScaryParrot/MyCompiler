#pragma once

#include "../Order.cpp"
#include "../utils/Queue.cpp"

class OrderQueue
{
   public:
    OrderQueue() = default;
    OrderQueue(Order order) { this->queue.Enqueue(order); }

    void Enqueue(Order order) { this->queue.Enqueue(order); }
    Order Dequeue() { return this->queue.Dequeue(); }
    Order Front() { return this->queue.Front(); }
    bool IsEmpty() { return this->queue.IsEmpty(); }
    void Clear() { this->queue.Clear(); }

    std::string ToString()
    {
        Queue<Order> tempQueue = this->queue;

        std::string str = "";

        while (!tempQueue.IsEmpty())
        {
            Order order = tempQueue.Dequeue();
            str += order.ToString() + "\n";
        }

        return str;
    }

   private:
    Queue<Order> queue;
};