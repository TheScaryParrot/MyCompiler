#pragma once

#include "AbstractKeywordStatementNode.cpp"

class ContinueStatementNode : public AbstractKeywordStatementNode
{
public:
    ContinueStatementNode();
    ~ContinueStatementNode();

    virtual std::string ToString() override;
};

ContinueStatementNode::ContinueStatementNode() : AbstractKeywordStatementNode()
{
}

ContinueStatementNode::~ContinueStatementNode()
{
}

std::string ContinueStatementNode::ToString()
{
    return "continue";
}