#pragma once

#include "../BodyNode.cpp"
#include "AbstractVarFuncDeclarationNode.cpp"
#include "ParameterDeclarationNode.cpp"
#include "declarationAttributes/DeclarationAttributes.cpp"
#include "types/FunctionReturnTypeNode.cpp"

class FuncDeclarationNode : public AbstractVarFuncDeclarationNode
{
   public:
    FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name,
                        std::vector<ParameterDeclarationNode*>* parameters, AbstractStatementNode* statement);
    ~FuncDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    DeclarationAttributes attributes;
    AbstractStatementNode* statement;
};

FuncDeclarationNode::FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType,
                                         std::string name, std::vector<ParameterDeclarationNode*>* parameters,
                                         AbstractStatementNode* statement)
    : AbstractVarFuncDeclarationNode()
{
    this->attributes = attributes;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
    this->statement = statement;
}

FuncDeclarationNode::~FuncDeclarationNode()
{
    for (ParameterDeclarationNode* parameter : *parameters)
    {
        delete parameter;
    }

    delete parameters;

    delete statement;
}

std::string FuncDeclarationNode::ToString()
{
    std::string result = "func: " + attributes.ToString() + " " + returnType.ToString() + " " + name + "(";

    for (ParameterDeclarationNode* parameter : *parameters)
    {
        result += parameter->ToString() + ", ";
    }

    return result + ")" + statement->ToString();
}