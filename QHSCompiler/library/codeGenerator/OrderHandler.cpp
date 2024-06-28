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
    OrderHandler();
    OrderHandler(InputFile* file);

    Order GetCurrentOrder();

    /// @brief Advances next order; order can be retrieved from GetCurrentOrder()
    void NextOrder();

    void PutInFront(OrderQueue queue);

    bool IsDone();

   private:
    Order currentOrder = Order::Empty();

    Scanner scanner;
    InputFile* file;

    Stack<OrderQueue*> stackedOrderQueues;
};

OrderHandler::OrderHandler() {}

OrderHandler::OrderHandler(InputFile* file)
{
    this->file = file;
    this->scanner = Scanner();
    this->stackedOrderQueues = Stack<OrderQueue*>();
    this->NextOrder();  // Immediately get the first order
}

Order OrderHandler::GetCurrentOrder() { return currentOrder; }

void OrderHandler::NextOrder()
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
        stackedOrderQueues.Pop();
    }

    currentOrder = order;
}

void OrderHandler::PutInFront(OrderQueue queue)
{
    if (queue.IsEmpty())
    {
        return;
    }

    OrderQueue* newQueue = new OrderQueue(queue);

    stackedOrderQueues.Push(newQueue);
}

bool OrderHandler::IsDone() { return stackedOrderQueues.IsEmpty() && file->IsEndOfFile(); }