#pragma once

#include "../AbstractLineChildNode.cpp"

class AbstractDeclarationNode : public AbstractLineChildNode
{
public:
    AbstractDeclarationNode();
    virtual ~AbstractDeclarationNode();
};

AbstractDeclarationNode::AbstractDeclarationNode() : AbstractLineChildNode()
{
}

AbstractDeclarationNode::~AbstractDeclarationNode()
{
}