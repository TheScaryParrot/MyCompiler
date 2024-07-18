#pragma once

#include "AbstractDeclarationNode.cpp"
#include "types/TypeNode.cpp"

class PropertyDeclarationNode : public AbstractDeclarationNode
{
   public:
    PropertyDeclarationNode(TypeNode type, std::string name)
    {
        this->type = type;
        this->name = name;
    }

    virtual std::string ToString() override { return "property " + type.ToString() + " " + name + ";"; };

    std::string name;
    TypeNode type;
};