#pragma once

#include <memory>

#include "../InputFile.cpp"
#include "../Order.cpp"
#include "../scanner/Scanner.cpp"
#include "../utils/Queue.cpp"
#include "../utils/Stack.cpp"

class OrderHandler
{
   public:
    OrderHandler();
    OrderHandler(InputFile* file);

    Order GetNextOrder();

    void PutInFront(Queue<Order> queue);

    bool IsDone();

   private:
    Scanner scanner;
    InputFile* file;

    Stack<Queue<Order>*> stackedOrderQueues = Stack<Queue<Order>*>();
};

OrderHandler::OrderHandler() {}

OrderHandler::OrderHandler(InputFile* file)
{
    this->file = file;
    this->scanner = Scanner();
}

Order OrderHandler::GetNextOrder()
{
    if (stackedOrderQueues.IsEmpty())
    {
        return scanner.ScanOrder(file);
    }

    Queue<Order>* queue = stackedOrderQueues.Top();
    Order order = queue->Dequeue();

    if (queue->IsEmpty())
    {
        stackedOrderQueues.Pop();
    }

    return order;
}

void OrderHandler::PutInFront(Queue<Order> queue)
{
    if (queue.IsEmpty())
    {
        return;
    }

    Queue<Order>* newQueue = new Queue<Order>(queue);

    stackedOrderQueues.Push(newQueue);
}

bool OrderHandler::IsDone() { return stackedOrderQueues.IsEmpty() && file->IsEndOfFile(); }