#pragma once

#include "AbstractKeywordStatementNode.cpp"

class BreakStatementNode : public AbstractKeywordStatementNode
{
public:
    BreakStatementNode();
    ~BreakStatementNode();

    virtual std::string ToString() override;
};

BreakStatementNode::BreakStatementNode() : AbstractKeywordStatementNode()
{
}

BreakStatementNode::~BreakStatementNode()
{
}

std::string BreakStatementNode::ToString()
{
    return "continue";
}