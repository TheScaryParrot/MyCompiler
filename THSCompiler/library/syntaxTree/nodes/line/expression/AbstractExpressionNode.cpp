#pragma once

#include "../statement/AbstractStatementNode.cpp"

/// @brief Node used for everything that is an expression. So also sumExp or unaryExp
class AbstractExpressionNode : public AbstractStatementNode
{
public:
    AbstractExpressionNode();
    virtual ~AbstractExpressionNode();
};

AbstractExpressionNode::AbstractExpressionNode() : AbstractStatementNode()
{

}

AbstractExpressionNode::~AbstractExpressionNode()
{
    
}