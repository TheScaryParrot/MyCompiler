#pragma once

#include "../utils/Stack.cpp"
#include "OrderQueue.cpp"

class OrderStackHandler
{
   public:
    void NewStack();
    void PushOrder(Order order);
    OrderQueue PopOrderQueue();

   private:
    Stack<OrderQueue*> stack;
};

void OrderStackHandler::NewStack() { stack.Push(new OrderQueue()); }

void OrderStackHandler::PushOrder(Order order) { stack.Top()->Enqueue(order); }

OrderQueue OrderStackHandler::PopOrderQueue() { return *stack.Pop(); }