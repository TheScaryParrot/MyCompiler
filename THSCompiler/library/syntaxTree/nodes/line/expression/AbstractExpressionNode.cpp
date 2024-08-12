#pragma once

#include "../statement/AbstractStatementNode.cpp"

/// @brief Node used for everything that is an expression. So also sumExp or unaryExp
class AbstractExpressionNode : public AbstractStatementNode
{
   public:
    AbstractExpressionNode();
    virtual ~AbstractExpressionNode();

    virtual bool RequiresAXRegister() = 0;
};

AbstractExpressionNode::AbstractExpressionNode() : AbstractStatementNode() {}

AbstractExpressionNode::~AbstractExpressionNode() {}