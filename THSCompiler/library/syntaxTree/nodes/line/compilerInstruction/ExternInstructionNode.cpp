#pragma once

#include <vector>

#include "../declaration/ParameterDeclarationNode.cpp"
#include "../declaration/types/FunctionReturnTypeNode.cpp"
#include "AbstractCompilerInstructionNode.cpp"

class ExternInstructionNode : public AbstractCompilerInstructionNode
{
   public:
    FunctionReturnTypeNode returnType;
    std::string identifier;
    std::vector<ParameterDeclarationNode*>* parameters;

    ExternInstructionNode(FunctionReturnTypeNode returnType, std::string identifier, std::vector<ParameterDeclarationNode*>* parameters)
        : AbstractCompilerInstructionNode()
    {
        this->returnType = returnType;
        this->identifier = identifier;
        this->parameters = parameters;
    }

    ~ExternInstructionNode()
    {
        for (ParameterDeclarationNode* parameter : *parameters)
        {
            delete parameter;
        }

        delete parameters;
    }

    virtual std::string ToString() override
    {
        std::string result = "extern " + returnType.ToString() + " " + identifier + "(";

        for (ParameterDeclarationNode* parameter : *parameters)
        {
            result += parameter->ToString() + ", ";
        }

        return result + ");";
    }
};