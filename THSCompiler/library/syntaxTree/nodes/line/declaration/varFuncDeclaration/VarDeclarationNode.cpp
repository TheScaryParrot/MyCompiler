#pragma once

#include "AbstractVarFuncDeclarationNode.cpp"

#include "declarationAttributes/DeclarationAttributes.cpp"
#include "../../expression/AbstractExpressionNode.cpp"

class VarDeclarationNode : public AbstractVarFuncDeclarationNode
{
public:
    VarDeclarationNode(DeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value = nullptr);
    ~VarDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    TypeNode type;
    AbstractExpressionNode* value;
    DeclarationAttributes attributes;
};

VarDeclarationNode::VarDeclarationNode(DeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value) : AbstractVarFuncDeclarationNode()
{
    this->attributes = attributes;
    this->type = type;
    this->name = name;
    this->value = value;
}

VarDeclarationNode::~VarDeclarationNode()
{
    delete value;
}

std::string VarDeclarationNode::ToString()
{
    std::string result = attributes.ToString() + type.ToString() + " " + name;

    if (value != nullptr)
    {
        result += " = " + value->ToString();
    }

    return result + ";";
}