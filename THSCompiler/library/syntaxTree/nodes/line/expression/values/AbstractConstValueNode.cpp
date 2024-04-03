#pragma once 

#include "../AbstractValueNode.cpp"

class AbstractConstValueNode : public AbstractValueNode
{
public:
    AbstractConstValueNode();
    virtual ~AbstractConstValueNode();
};

AbstractConstValueNode::AbstractConstValueNode() : AbstractValueNode()
{
}

AbstractConstValueNode::~AbstractConstValueNode()
{
}