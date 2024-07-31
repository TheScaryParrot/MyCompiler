#pragma once

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ElifStatementNode : public AbstractKeywordStatementNode
{
   public:
    ElifStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement);
    ~ElifStatementNode();

    virtual std::string ToString() override;

    AbstractExpressionNode* expression;
    AbstractStatementNode* statement;
};

ElifStatementNode::ElifStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement) : AbstractKeywordStatementNode()
{
    this->expression = expression;
    this->statement = statement;
}

ElifStatementNode::~ElifStatementNode()
{
    delete expression;
    delete statement;
}

std::string ElifStatementNode::ToString() { return "elif (" + expression->ToString() + ")\n" + statement->ToString(); }