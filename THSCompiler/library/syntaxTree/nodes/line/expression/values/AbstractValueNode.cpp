#pragma once

#include "../AbstractExpressionNode.cpp"

class AbstractValueNode : public AbstractExpressionNode
{
   public:
    AbstractValueNode();
    virtual ~AbstractValueNode();
};

AbstractValueNode::AbstractValueNode() : AbstractExpressionNode() {}

AbstractValueNode::~AbstractValueNode() {}
