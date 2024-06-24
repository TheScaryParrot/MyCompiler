#pragma once

#include <vector>

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class WhileStatementNode : public AbstractKeywordStatementNode
{
   public:
    WhileStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement);
    ~WhileStatementNode();

    virtual std::string ToString() override;

    AbstractExpressionNode* expression;
    AbstractStatementNode* statement;
};

WhileStatementNode::WhileStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement)
    : AbstractKeywordStatementNode()
{
    this->expression = expression;
    this->statement = statement;
}

WhileStatementNode::~WhileStatementNode()
{
    delete expression;
    delete statement;
}

std::string WhileStatementNode::ToString()
{
    return "while (" + expression->ToString() + ")\n" + statement->ToString();
}