#pragma once

#include "AbstractExpressionNode.cpp"

class ValueNode : AbstractExpressionNode
{
public:
    ValueNode();
    ~ValueNode();

    virtual std::string ToString() override;
};