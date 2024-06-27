#pragma once

#include <vector>

#include "../Order.cpp"
#include "../utils/Queue.cpp"
#include "Type.cpp"

class Callable
{
   public:
    Callable(std::vector<Type*> pushTypes, std::vector<Type*> popTypes, Queue<Order> orders);

    void SetPushTypes(std::vector<Type*> types);
    void SetPopTypes(std::vector<Type*> types);

    void SetOrders(Queue<Order> orders);
    Queue<Order> GetOrders();

    void MakeCodeStackProof();
    bool IsCodeStackProof();

    void MakeCommentProof();
    bool IsCommentProof();

   private:
    std::vector<Type*> pushTypes;
    std::vector<Type*> popTypes;
    Queue<Order> orders;

    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

Callable::Callable(std::vector<Type*> pushTypes, std::vector<Type*> popTypes, Queue<Order> orders)
{
    SetPushTypes(pushTypes);
    SetPopTypes(popTypes);
    SetOrders(orders);
}

void Callable::SetPushTypes(std::vector<Type*> types) { pushTypes = types; }

void Callable::SetPopTypes(std::vector<Type*> types) { popTypes = types; }

void Callable::SetOrders(Queue<Order> orders) { this->orders = orders; }

Queue<Order> Callable::GetOrders() { return orders; }

void Callable::MakeCodeStackProof() { isCodeStackProof = true; }

bool Callable::IsCodeStackProof() { return isCodeStackProof; }

void Callable::MakeCommentProof() { isCommentProof = true; }

bool Callable::IsCommentProof() { return isCommentProof; }