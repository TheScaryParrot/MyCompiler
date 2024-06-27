#pragma once

#include <vector>

#include "../OrderQueue.cpp"
#include "Type.cpp"

class Callable
{
   public:
    Callable(std::vector<Type*> pushTypes, std::vector<Type*> popTypes, OrderQueue orders);

    void SetPushTypes(std::vector<Type*> types);
    void SetPopTypes(std::vector<Type*> types);

    void SetOrders(OrderQueue orders);
    OrderQueue GetOrders();

    void MakeCodeStackProof();
    bool IsCodeStackProof();

    void MakeCommentProof();
    bool IsCommentProof();

   private:
    std::vector<Type*> pushTypes;
    std::vector<Type*> popTypes;
    OrderQueue orders;

    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

Callable::Callable(std::vector<Type*> pushTypes, std::vector<Type*> popTypes, OrderQueue orders)
{
    SetPushTypes(pushTypes);
    SetPopTypes(popTypes);
    SetOrders(orders);
}

void Callable::SetPushTypes(std::vector<Type*> types) { pushTypes = types; }

void Callable::SetPopTypes(std::vector<Type*> types) { popTypes = types; }

void Callable::SetOrders(OrderQueue orders) { this->orders = orders; }

OrderQueue Callable::GetOrders() { return orders; }

void Callable::MakeCodeStackProof() { isCodeStackProof = true; }

bool Callable::IsCodeStackProof() { return isCodeStackProof; }

void Callable::MakeCommentProof() { isCommentProof = true; }

bool Callable::IsCommentProof() { return isCommentProof; }