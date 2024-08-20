#pragma once

#include <string>

class Order
{
   public:
    enum EOrderTypes
    {
        Identifier,
        Instruction,
        LiteralCode
    };

    Order(Order const& order)
    {
        this->name = order.name;
        this->type = order.type;
    }

    Order(std::string name, EOrderTypes type)
    {
        this->name = name;
        this->type = type;
    }

    std::string GetName() { return this->name; }
    EOrderTypes GetType() { return this->type; }

    std::string ToString()
    {
        std::string result = GetName();

        switch (GetType())
        {
            case EOrderTypes::Identifier:
                break;
            case EOrderTypes::Instruction:
                result += " (Compiler Instruction)";
                break;
            case EOrderTypes::LiteralCode:
                result += " (Direct Code)";
                break;
        }

        return result;
    }

    static Order Empty() { return Order("EMPTY", EOrderTypes::Identifier); }

   private:
    std::string name;
    EOrderTypes type = EOrderTypes::Identifier;
};