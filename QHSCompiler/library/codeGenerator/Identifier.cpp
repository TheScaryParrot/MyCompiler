#pragma once

#include <vector>

#include "../Order.cpp"
#include "Callable.cpp"
#include "OrderQueue.cpp"
#include "Type.cpp"

class Identifier : public Callable
{
   public:
    Identifier(OrderQueue orders)
        : Callable([orders](ICodeGenerator* codeGenerator) { codeGenerator->PutInFront(orders); })
    {
    }

    void SetOrders(OrderQueue orders)
    {
        SetFunction([orders](ICodeGenerator* codeGenerator) { codeGenerator->PutInFront(orders); });
    }
};
