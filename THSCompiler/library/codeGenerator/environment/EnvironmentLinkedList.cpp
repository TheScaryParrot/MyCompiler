#pragma once

#include "Environment.cpp"

struct EnvironmentLinkedListElement
{
    Environment* self;
    EnvironmentLinkedListElement* next;
};

class EnvironmentLinkedList
{
   public:
    void Push(Environment* environment)
    {
        EnvironmentLinkedListElement* newElement = new EnvironmentLinkedListElement();
        newElement->self = environment;
        newElement->next = head;
        head = newElement;
    }

    Environment* Pop()
    {
        if (head == nullptr) return nullptr;

        EnvironmentLinkedListElement* oldHead = head;
        Environment* oldEnvironment = oldHead->self;
        head = head->next;
        delete oldHead;  // deleting does not delete the Environment, only the EnvironmentLinkedListElement
        return oldEnvironment;
    }

   private:
    EnvironmentLinkedListElement* head;
};
