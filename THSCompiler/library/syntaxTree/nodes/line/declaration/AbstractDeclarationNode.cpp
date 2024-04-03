#pragma once

#include "../AbstractLineNode.cpp"

class AbstractDeclarationNode : public AbstractLineNode
{
public:
    AbstractDeclarationNode();
    virtual ~AbstractDeclarationNode();
};

AbstractDeclarationNode::AbstractDeclarationNode() : AbstractLineNode()
{
}

AbstractDeclarationNode::~AbstractDeclarationNode()
{
}