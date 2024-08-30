#pragma once

#include <vector>

#include "Order.cpp"

class OrderQueue
{
    struct Node
    {
        Order order = Order::Empty();
        Node* next;
        Node* prev;
    };

   public:
    OrderQueue() = default;
    OrderQueue(Order order) { this->Enqueue(order); }

    void Enqueue(Order order)
    {
        Node* newNode = new Node();
        newNode->order = order;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void EnqueueInFront(Order order)
    {
        Node* newNode = new Node();
        newNode->order = order;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    Order Dequeue()
    {
        if (IsEmpty()) return Order::Empty();

        Node* current = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        return current->order;
    }
    Order Front() { return this->head->order; }
    bool IsEmpty() { return this->head == nullptr; }
    void Clear()
    {
        while (!IsEmpty()) Dequeue();
    }

    std::string ToString()
    {
        std::string str = "";

        Node* current = head;

        while (current != nullptr)
        {
            str += current->order.ToString() + "\n";
            current = current->next;
        }

        return str;
    }

   private:
    Node* head = nullptr;
    Node* tail = nullptr;
};