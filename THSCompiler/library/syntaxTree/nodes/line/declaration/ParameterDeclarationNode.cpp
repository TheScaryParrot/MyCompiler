#pragma once

#include "AbstractDeclarationNode.cpp"

class ParameterDeclarationNode : public AbstractDeclarationNode
{
   public:
    ParameterDeclarationNode(bool isFinal, std::string type, std::string name)
    {
        this->isFinal = isFinal;
        this->type = type;
        this->name = name;
    }

    virtual std::string ToString() override
    {
        std::string result = "param ";

        if (isFinal) result += "final ";

        return result + type + " " + name;
    }

    std::string name;
    std::string type;

    bool isFinal;
};