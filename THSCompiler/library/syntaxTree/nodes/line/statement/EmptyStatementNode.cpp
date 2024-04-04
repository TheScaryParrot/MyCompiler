#pragma once

#include "AbstractStatementNode.cpp"

class EmptyStatementNode : public AbstractStatementNode
{
public:
    EmptyStatementNode();
    ~EmptyStatementNode();

    virtual std::string ToString() override;
};

EmptyStatementNode::EmptyStatementNode() : AbstractStatementNode()
{
}

EmptyStatementNode::~EmptyStatementNode()
{
}

std::string EmptyStatementNode::ToString()
{
    return ";";
}