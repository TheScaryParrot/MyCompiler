#pragma once

#include "AbstractVarDeclarationNode.cpp"

class GlobalVarDeclarationNode : public AbstractVarDeclarationNode
{
   public:
    GlobalVarDeclarationNode(VarDeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value)
        : AbstractVarDeclarationNode(attributes, type, name, value)
    {
    }

    virtual std::string ToString() override { return "global " + AbstractVarDeclarationNode::ToString(); }
};