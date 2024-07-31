#pragma once

#include <vector>

#include "../../declaration/ParameterDeclarationNode.cpp"
#include "../../declaration/types/FunctionReturnTypeNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ExternStatementNode : public AbstractKeywordStatementNode
{
   public:
    FunctionReturnTypeNode returnType;
    std::string identifier;
    std::vector<ParameterDeclarationNode*>* parameters;

    ExternStatementNode(FunctionReturnTypeNode returnType, std::string identifier, std::vector<ParameterDeclarationNode*>* parameters)
    {
        this->returnType = returnType;
        this->identifier = identifier;
        this->parameters = parameters;
    }

    ~ExternStatementNode()
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