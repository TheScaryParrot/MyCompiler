#pragma once

#include "../AbstractLineChildNode.cpp"

class AbstractStatementNode : public AbstractLineChildNode
{
public:
    AbstractStatementNode();
    virtual ~AbstractStatementNode();
};

AbstractStatementNode::AbstractStatementNode() : AbstractLineChildNode()
{
}

AbstractStatementNode::~AbstractStatementNode()
{
}
