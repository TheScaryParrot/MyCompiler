#pragma once

#include "../statement/BodyNode.cpp"
#include "AbstractDeclarationNode.cpp"
#include "DeclarationAttributes.cpp"
#include "ParameterDeclarationNode.cpp"
#include "types/FunctionReturnTypeNode.cpp"

class FuncDeclarationNode : public AbstractDeclarationNode
{
   public:
    FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name,
                        std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body);
    ~FuncDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    DeclarationAttributes attributes;
    BodyNode* body;
};

FuncDeclarationNode::FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name,
                                         std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body)
    : AbstractDeclarationNode()
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
    std::string result = attributes.ToString() + " " + returnType.ToString() + " " + name + "(";

    for (ParameterDeclarationNode* parameter : *parameters)
    {
        result += parameter->ToString() + ", ";
    }

    return result + ")" + body->ToString();
}