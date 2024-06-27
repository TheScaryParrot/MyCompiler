#pragma once

#include <iostream>
#include <memory>
#include <queue>

#include "Order.cpp"

class OrderQueue
{
   public:
    void Push(Order order);
    void PushQueue(OrderQueue queue);

    // TODO: This is probably quite inefficient; maybe create linkedList of queues?
    void PushFront(Order order);
    void PushFrontQueue(OrderQueue queue);
    Order Pop();
    Order Front();
    bool IsEmpty();

    /// @brief Pops the whole queue and returns a string with all the orders
    std::string CollapseToString();

   private:
    std::queue<Order> orders = std::queue<Order>();
};

void OrderQueue::Push(Order order) { orders.push(order); }

void OrderQueue::PushQueue(OrderQueue other)
{
    while (!other.IsEmpty())
    {
        this->Push(other.Pop());
    }
}

void OrderQueue::PushFront(Order order)
{
    std::queue<Order> newQueue = std::queue<Order>();
    newQueue.push(order);

    while (!orders.empty())
    {
        newQueue.push(orders.front());
        orders.pop();
    }

    orders = newQueue;
}

void OrderQueue::PushFrontQueue(OrderQueue other)
{
    std::queue<Order> newQueue = std::queue<Order>();

    while (!other.IsEmpty())
    {
        newQueue.push(other.Pop());
    }

    while (!orders.empty())
    {
        newQueue.push(orders.front());
        orders.pop();
    }

    orders = newQueue;
}

Order OrderQueue::Pop()
{
    Order order = Front();
    orders.pop();
    return order;
}

Order OrderQueue::Front() { return orders.front(); }

bool OrderQueue::IsEmpty() { return orders.empty(); }

std::string OrderQueue::CollapseToString()
{
    std::string result = "";

    while (!orders.empty())
    {
        result += orders.front().ToString();
        orders.pop();
        result += "\n";
    }

    return result;
}
