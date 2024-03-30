#pragma once

#include "AbstractVarFuncDeclarationNode.cpp"

#include "declarationAttributes/DeclarationAttributes.cpp"
#include "ParameterDeclarationNode.cpp"
#include "types/FunctionReturnTypeNode.cpp"

class FuncDeclarationNode : public AbstractVarFuncDeclarationNode
{
public:
    FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name, std::vector<ParameterDeclarationNode*>* parameters);
    ~FuncDeclarationNode();

    virtual std::string ToString() override;

private:
    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    DeclarationAttributes attributes;

    //TODO Add body
};

FuncDeclarationNode::FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name, std::vector<ParameterDeclarationNode*>* parameters) : AbstractVarFuncDeclarationNode()
{
    this->attributes = attributes;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
}

FuncDeclarationNode::~FuncDeclarationNode()
{
    for (ParameterDeclarationNode* parameter : *parameters)
    {
        delete parameter;
    }

    delete parameters;
}

std::string FuncDeclarationNode::ToString()
{
    std::string result = "func: ATTRIBUTES TYPE" + name + "(";

    for (ParameterDeclarationNode* parameter : *parameters)
    {
        result += parameter->ToString() + ", ";
    }

    result += ");";

    return result;
}