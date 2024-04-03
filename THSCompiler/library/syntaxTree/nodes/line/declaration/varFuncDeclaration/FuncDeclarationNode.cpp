#pragma once

#include "AbstractVarFuncDeclarationNode.cpp"

#include "declarationAttributes/DeclarationAttributes.cpp"
#include "ParameterDeclarationNode.cpp"
#include "types/FunctionReturnTypeNode.cpp"
#include "../BodyNode.cpp"

class FuncDeclarationNode : public AbstractVarFuncDeclarationNode
{
public:
    FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name, 
                        std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body);
    ~FuncDeclarationNode();

    virtual std::string ToString() override;

private:
    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    DeclarationAttributes attributes;
    BodyNode* bodyNode;
};

FuncDeclarationNode::FuncDeclarationNode(DeclarationAttributes attributes, FunctionReturnTypeNode returnType, std::string name, 
                                    std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body) : AbstractVarFuncDeclarationNode()
{
    this->attributes = attributes;
    this->returnType = returnType;
    this->name = name;
    this->parameters = parameters;
    this->bodyNode = bodyNode;
}

FuncDeclarationNode::~FuncDeclarationNode()
{
    for (ParameterDeclarationNode* parameter : *parameters)
    {
        delete parameter;
    }

    delete parameters;

    delete bodyNode;
}

std::string FuncDeclarationNode::ToString()
{
    std::string result = "func: " + attributes.ToString() + " " + returnType.ToString() + " " + name + "(";

    for (ParameterDeclarationNode* parameter : *parameters)
    {
        result += parameter->ToString() + ", ";
    }

    result += ")";

    if (bodyNode != nullptr) result += bodyNode->ToString();
    else result += ";";

    return result;
}