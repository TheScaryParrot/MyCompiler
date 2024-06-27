#pragma once

#include <string>

class Order
{
   public:
    enum EOrderTypes
    {
        Identifier,
        CompilerInstruction,
        DirectCode
    };

    Order(std::string name, EOrderTypes type)
    {
        this->name = name;
        this->type = type;
    }

    std::string GetName();
    EOrderTypes GetType();

    std::string ToString();

    static Order Empty() { return Order("EMPTY", EOrderTypes::Identifier); }

   private:
    std::string name;
    EOrderTypes type = EOrderTypes::Identifier;
};

std::string Order::GetName() { return this->name; }

Order::EOrderTypes Order::GetType() { return this->type; }

std::string Order::ToString()
{
    std::string result = GetName();

    switch (GetType())
    {
        case EOrderTypes::Identifier:
            break;
        case EOrderTypes::CompilerInstruction:
            result += " (Compiler Instruction)";
            break;
    }

    return result;
}