#pragma once

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ReturnStatementNode : public AbstractKeywordStatementNode
{
   public:
    ReturnStatementNode(AbstractExpressionNode* expression);
    ~ReturnStatementNode();

    virtual std::string ToString() override;

    AbstractExpressionNode* expression;
};

ReturnStatementNode::ReturnStatementNode(AbstractExpressionNode* expression) : AbstractKeywordStatementNode()
{
    this->expression = expression;
}

ReturnStatementNode::~ReturnStatementNode() { delete expression; }

std::string ReturnStatementNode::ToString() { return "return " + expression->ToString(); }