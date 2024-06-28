#pragma once

#include <vector>

#include "../Order.cpp"
#include "../utils/Queue.cpp"
#include "Callable.cpp"
#include "Type.cpp"

class Identifier : public Callable
{
   public:
    Identifier(std::vector<Type*> pushTypes, std::vector<Type*> popTypes, Queue<Order> orders);

    void SetPushTypes(std::vector<Type*> types);
    void SetPopTypes(std::vector<Type*> types);

    void SetOrders(Queue<Order> orders);

    void MakeCodeStackProof();
    bool IsCodeStackProof();

    void MakeCommentProof();
    bool IsCommentProof();

   private:
    std::vector<Type*> pushTypes;
    std::vector<Type*> popTypes;

    bool isCodeStackProof = false;
    bool isCommentProof = false;
};

Identifier::Identifier(std::vector<Type*> pushTypes, std::vector<Type*> popTypes, Queue<Order> orders)
    : Callable([orders](ICodeGenerator* codeGenerator) { codeGenerator->PutInFront(orders); })
{
    SetPushTypes(pushTypes);
    SetPopTypes(popTypes);
}

void Identifier::SetPushTypes(std::vector<Type*> types) { pushTypes = types; }

void Identifier::SetPopTypes(std::vector<Type*> types) { popTypes = types; }

void Identifier::MakeCodeStackProof() { isCodeStackProof = true; }

bool Identifier::IsCodeStackProof() { return isCodeStackProof; }

void Identifier::MakeCommentProof() { isCommentProof = true; }

bool Identifier::IsCommentProof() { return isCommentProof; }