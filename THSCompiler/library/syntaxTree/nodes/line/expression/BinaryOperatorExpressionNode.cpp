#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"
#include "operators/OperatorExpressionPair.cpp"

class BinaryOperatorExpressionNode : public AbstractExpressionNode
{
   public:
    BinaryOperatorExpressionNode(AbstractExpressionNode* firstExpression,
                                 std::vector<OperatorExpressionPair*>* OperatorValuePairs = nullptr);
    ~BinaryOperatorExpressionNode();

    virtual std::string ToString() override;

    AbstractExpressionNode* firstExpression;
    std::vector<OperatorExpressionPair*>* operatorExpressionPairs;
};

BinaryOperatorExpressionNode::BinaryOperatorExpressionNode(
    AbstractExpressionNode* firstExpression, std::vector<OperatorExpressionPair*>* operatorExpressionPairs)
    : AbstractExpressionNode()
{
    this->firstExpression = firstExpression;
    this->operatorExpressionPairs = operatorExpressionPairs;
}

BinaryOperatorExpressionNode::~BinaryOperatorExpressionNode()
{
    delete firstExpression;

    for (OperatorExpressionPair* pair : *operatorExpressionPairs)
    {
        delete pair;
    }
    delete operatorExpressionPairs;
}

std::string BinaryOperatorExpressionNode::ToString()
{
    std::string result = firstExpression->ToString();

    if (operatorExpressionPairs == nullptr)
    {
        return result;
    }

    for (OperatorExpressionPair* pair : *operatorExpressionPairs)
    {
        result += pair->ToString();
    }

    return result;
}
