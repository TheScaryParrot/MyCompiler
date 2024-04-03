#pragma once

#include "AbstractExpressionNode.cpp"

#include "ValueNode.cpp"
#include "operators/EUnaryOperators.cpp"

class UnaryExpressionNode : AbstractExpressionNode
{
public:
    UnaryExpressionNode(EUnaryOperators unaryOperator, ValueNode* value);
    ~UnaryExpressionNode();

    virtual std::string ToString() override;

private:
    EUnaryOperators unaryOperator;
    ValueNode* value;
};

UnaryExpressionNode::UnaryExpressionNode(EUnaryOperators unaryOperator, ValueNode* value) : AbstractExpressionNode()
{
    this->unaryOperator = unaryOperator;
    this->value = value;
}

UnaryExpressionNode::~UnaryExpressionNode()
{
    delete value;
}

std::string UnaryExpressionNode::ToString()
{
    return EUnaryOperatorsToString(unaryOperator) + value->ToString();
}
