#pragma once

#include "../../AbstractTreeNode.cpp"

/// @brief Node used for everything that is an expression. So also sumExp or unaryExp
class AbstractExpressionNode : public AbstractTreeNode
{
public:
    AbstractExpressionNode();
    virtual ~AbstractExpressionNode();
};

AbstractExpressionNode::AbstractExpressionNode() : AbstractTreeNode()
{

}

AbstractExpressionNode::~AbstractExpressionNode()
{
    
}