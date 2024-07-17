#pragma once

#include "../expression/AbstractExpressionNode.cpp"
#include "AbstractDeclarationNode.cpp"
#include "DeclarationAttributes.cpp"
#include "types/TypeNode.cpp"

class VarDeclarationNode : public AbstractDeclarationNode
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

VarDeclarationNode::VarDeclarationNode(DeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value)
    : AbstractDeclarationNode()
{
    this->attributes = attributes;
    this->type = type;
    this->name = name;
    this->value = value;
}

VarDeclarationNode::~VarDeclarationNode() { delete value; }

std::string VarDeclarationNode::ToString()
{
    std::string result = attributes.ToString() + type.ToString() + " " + name;

    if (value != nullptr)
    {
        result += " = " + value->ToString();
    }

    return result + ";";
}