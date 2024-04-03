#pragma once

#include "EOperators.cpp"
#include "../AbstractExpressionNode.cpp"

class OperatorExpressionPair
{
public:
    OperatorExpressionPair(EOperators op, AbstractExpressionNode* expression);
    ~OperatorExpressionPair();

    std::string ToString();

private:
    EOperators op; // operator
    AbstractExpressionNode* expression;
};

OperatorExpressionPair::OperatorExpressionPair(EOperators op, AbstractExpressionNode* expression)
{
    this->op = op;
    this->expression = expression;
}

OperatorExpressionPair::~OperatorExpressionPair()
{
    delete expression;
}

std::string OperatorExpressionPair::ToString()
{
    return EOperatorsToString(op) + expression->ToString();
}