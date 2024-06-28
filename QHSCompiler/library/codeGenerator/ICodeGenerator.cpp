#pragma once

#include "../Order.cpp"
#include "../utils/Logger.cpp"
#include "../utils/Queue.cpp"

class ICodeGenerator
{
   public:
    enum EModes
    {
        CallableStack,
        CodeStack,
        TypeStack,
        Comment
    };

    virtual void PutInFront(Queue<Order> orders) = 0;
};