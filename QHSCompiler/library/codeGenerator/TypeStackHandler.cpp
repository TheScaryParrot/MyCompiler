#pragma once

#include <vector>

#include "../utils/Stack.cpp"
#include "Type.cpp"

class TypeStackHandler
{
   public:
    void NewStack();
    void PushType(Type* type);
    std::vector<Type*> PopStack();

   private:
    Stack<Stack<Type*>> typeStack = Stack<Stack<Type*>>();
};

void TypeStackHandler::NewStack() { typeStack.Push(Stack<Type*>()); }

void TypeStackHandler::PushType(Type* type) { typeStack.Top().Push(type); }

std::vector<Type*> TypeStackHandler::PopStack()
{
    std::vector<Type*> types;

    Stack<Type*> stack = typeStack.Pop();

    while (!stack.IsEmpty())
    {
        types.push_back(stack.Pop());
    }

    return types;
}