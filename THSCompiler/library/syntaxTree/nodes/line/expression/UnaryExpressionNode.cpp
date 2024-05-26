#pragma once

#include "AbstractExpressionNode.cpp"

#include "operators/EUnaryOperators.cpp"

class UnaryExpressionNode : public AbstractExpressionNode
{
public:
    UnaryExpressionNode(EPreUnaryOperators preUnaryOperator, AbstractExpressionNode* value, EPostUnaryOperators postUnaryOperator);
    ~UnaryExpressionNode();

    virtual std::string ToString() override;

private:
    EPreUnaryOperators preUnaryOperator;
    AbstractExpressionNode* value;
    EPostUnaryOperators postUnaryOperator;
};

UnaryExpressionNode::UnaryExpressionNode(EPreUnaryOperators preUnaryOperator, AbstractExpressionNode* value, EPostUnaryOperators postUnaryOperator) : AbstractExpressionNode()
{
    this->preUnaryOperator = preUnaryOperator;
    this->value = value;
    this->postUnaryOperator = postUnaryOperator;
}

UnaryExpressionNode::~UnaryExpressionNode()
{
    delete value;
}

std::string UnaryExpressionNode::ToString()
{
    return EPreUnaryOperatorsToString(preUnaryOperator) + value->ToString() + EPostUnaryOperatorsToString(postUnaryOperator);
}
