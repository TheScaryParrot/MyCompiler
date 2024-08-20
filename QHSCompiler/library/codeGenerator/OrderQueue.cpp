#pragma once

#include <vector>

#include "Order.cpp"

class OrderQueue
{
   public:
    OrderQueue() = default;
    OrderQueue(Order order) { this->Enqueue(order); }

    void Enqueue(Order order) { this->queue.push_back(order); }
    void EnqueueInFront(Order order) { queue.insert(queue.begin(), order); }
    Order Dequeue()
    {
        if (IsEmpty()) return Order::Empty();

        Order order = this->queue.front();
        this->queue.erase(queue.begin());
        return order;
    }
    Order Front() { return this->queue.front(); }
    bool IsEmpty() { return this->queue.empty(); }
    void Clear()
    {
        while (!IsEmpty()) Dequeue();
    }

    std::string ToString()
    {
        std::vector<Order> tempQueue = this->queue;

        std::string str = "";

        while (!tempQueue.empty())
        {
            Order order = tempQueue.front();
            tempQueue.erase(queue.begin());
            str += order.ToString() + "\n";
        }

        return str;
    }

   private:
    std::vector<Order> queue;
};