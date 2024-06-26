#pragma once

#include "../BodyNode.cpp"
#include "AbstractVarFuncDeclarationNode.cpp"
#include "ParameterDeclarationNode.cpp"
#include "declarationAttributes/SyntaxTreeDeclarationAttributes.cpp"
#include "types/FunctionReturnTypeNode.cpp"

class FuncDeclarationNode : public AbstractVarFuncDeclarationNode
{
   public:
    FuncDeclarationNode(SyntaxTreeDeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name,
                        std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body);
    ~FuncDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    SyntaxTreeDeclarationAttributes attributes;
    BodyNode* body;
};

FuncDeclarationNode::FuncDeclarationNode(SyntaxTreeDeclarationAttributes attributes, FunctionReturnTypeNode returnType,
                                         std::string name, std::vector<ParameterDeclarationNode*>* parameters,
                                         BodyNode* body)
    : AbstractVarFuncDeclarationNode()
{
    this->attributes = attributes;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
    this->body = body;
}

FuncDeclarationNode::~FuncDeclarationNode()
{
    for (ParameterDeclarationNode* parameter : *parameters)
    {
        delete parameter;
    }

    delete parameters;

    delete body;
}

std::string FuncDeclarationNode::ToString()
{
    std::string result = "func: " + attributes.ToString() + " " + returnType.ToString() + " " + name + "(";

    for (ParameterDeclarationNode* parameter : *parameters)
    {
        result += parameter->ToString() + ", ";
    }

    return result + ")" + body->ToString();
}