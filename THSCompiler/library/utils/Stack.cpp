#pragma once

#include <stack>

template <typename T>
class Stack
{
   public:
    void Push(T value) { stack.push(value); }
    T Top()
    {
        if (stack.empty())
        {
            std::cerr << "Error: Stack is empty" << std::endl;
        }

        return stack.top();
    }
    T Pop()
    {
        if (stack.empty())
        {
            std::cerr << "Error: Stack is empty" << std::endl;
        }

        T value = stack.top();
        stack.pop();
        return value;
    }

   private:
    std::stack<T> stack;
};