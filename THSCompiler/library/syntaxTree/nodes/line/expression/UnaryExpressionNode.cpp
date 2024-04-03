#pragma once

#include "AbstractExpressionNode.cpp"

#include "operators/EUnaryOperators.cpp"

class UnaryExpressionNode : public AbstractExpressionNode
{
public:
    UnaryExpressionNode(EUnaryOperators unaryOperator, AbstractExpressionNode* value);
    ~UnaryExpressionNode();

    virtual std::string ToString() override;

private:
    EUnaryOperators unaryOperator;
    AbstractExpressionNode* value;
};

UnaryExpressionNode::UnaryExpressionNode(EUnaryOperators unaryOperator, AbstractExpressionNode* value) : AbstractExpressionNode()
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
