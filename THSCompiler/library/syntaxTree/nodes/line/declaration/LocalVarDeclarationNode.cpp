#pragma once

#include "AbstractVarDeclarationNode.cpp"

class LocalVarDeclarationNode : public AbstractVarDeclarationNode
{
   public:
    LocalVarDeclarationNode(VarDeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value)
        : AbstractVarDeclarationNode(attributes, type, name, value)
    {
    }

    virtual std::string ToString() override { return "local " + AbstractVarDeclarationNode::ToString(); }
};