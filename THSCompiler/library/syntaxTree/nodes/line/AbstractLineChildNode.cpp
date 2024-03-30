#pragma once

#include "../AbstractTreeNode.cpp"

class AbstractLineChildNode : public AbstractTreeNode
{
public:
    AbstractLineChildNode();
    virtual ~AbstractLineChildNode();
};

AbstractLineChildNode::AbstractLineChildNode() : AbstractTreeNode()
{
}

AbstractLineChildNode::~AbstractLineChildNode()
{
}