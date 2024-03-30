#pragma once

#include "../AbstractDeclarationNode.cpp"

class AbstractVarFuncDeclarationNode : public AbstractDeclarationNode
{
public:
    AbstractVarFuncDeclarationNode();
    virtual ~AbstractVarFuncDeclarationNode();
};

AbstractVarFuncDeclarationNode::AbstractVarFuncDeclarationNode() : AbstractDeclarationNode()
{
}

AbstractVarFuncDeclarationNode::~AbstractVarFuncDeclarationNode()
{
}