#pragma once

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractVarFuncDeclarationNode.cpp"
#include "declarationAttributes/SyntaxTreeDeclarationAttributes.cpp"
#include "types/TypeNode.cpp"

class VarDeclarationNode : public AbstractVarFuncDeclarationNode
{
   public:
    VarDeclarationNode(SyntaxTreeDeclarationAttributes attributes, TypeNode type, std::string name,
                       AbstractExpressionNode* value = nullptr);
    ~VarDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    TypeNode type;
    AbstractExpressionNode* value;
    SyntaxTreeDeclarationAttributes attributes;
};

VarDeclarationNode::VarDeclarationNode(SyntaxTreeDeclarationAttributes attributes, TypeNode type, std::string name,
                                       AbstractExpressionNode* value)
    : AbstractVarFuncDeclarationNode()
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