#pragma once

#include "../statement/BodyNode.cpp"
#include "AbstractDeclarationNode.cpp"
#include "ParameterDeclarationNode.cpp"
#include "types/FunctionReturnTypeNode.cpp"

class FuncDeclarationNode : public AbstractDeclarationNode
{
   public:
    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    BodyNode* body;

    FuncDeclarationNode(FunctionReturnTypeNode returnType, std::string name, std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body)
        : AbstractDeclarationNode()
    {
        this->returnType = returnType;
        this->name = name;
        this->parameters = parameters;
        this->body = body;
    }

    ~FuncDeclarationNode()
    {
        for (ParameterDeclarationNode* parameter : *parameters)
        {
            delete parameter;
        }

        delete parameters;

        delete body;
    }

    virtual std::string ToString() override
    {
        std::string result = returnType.ToString() + " " + name + "(";

        for (ParameterDeclarationNode* parameter : *parameters)
        {
            result += parameter->ToString() + ", ";
        }

        return result + ")" + body->ToString();
    }
};