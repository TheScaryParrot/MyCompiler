#pragma once

#include "AbstractVarFuncDeclarationNode.cpp"

#include "declarationAttributes/DeclarationAttributes.cpp"

class VarDeclarationNode : public AbstractVarFuncDeclarationNode
{
public:
    VarDeclarationNode(DeclarationAttributes attributes, TypeNode type, std::string name);
    ~VarDeclarationNode();

    virtual std::string ToString() override;

private:
    std::string name;
    TypeNode type;
    // TODO: Add value
    DeclarationAttributes attributes;
};

VarDeclarationNode::VarDeclarationNode(DeclarationAttributes attributes, TypeNode type, std::string name) : AbstractVarFuncDeclarationNode()
{
    this->attributes = attributes;
    this->type = type;
    this->name = name;
}

VarDeclarationNode::~VarDeclarationNode()
{
}

std::string VarDeclarationNode::ToString()
{
    return "var: ATTRIBUTES TYPE" + name + "= VALUE;";
}