#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"
#include "operators/OperatorExpressionPair.cpp"

class OperatorExpressionNode : public AbstractExpressionNode
{
   public:
    OperatorExpressionNode(AbstractExpressionNode* firstExpression,
                           std::vector<OperatorExpressionPair*>* OperatorValuePairs = nullptr);
    ~OperatorExpressionNode();

    virtual std::string ToString() override;

   private:
    AbstractExpressionNode* firstExpression;
    std::vector<OperatorExpressionPair*>* operatorExpressionPairs;
};

OperatorExpressionNode::OperatorExpressionNode(AbstractExpressionNode* firstExpression,
                                               std::vector<OperatorExpressionPair*>* operatorExpressionPairs)
    : AbstractExpressionNode()
{
    this->firstExpression = firstExpression;
    this->operatorExpressionPairs = operatorExpressionPairs;
}

OperatorExpressionNode::~OperatorExpressionNode()
{
    delete firstExpression;

    for (OperatorExpressionPair* pair : *operatorExpressionPairs)
    {
        delete pair;
    }
    delete operatorExpressionPairs;
}

std::string OperatorExpressionNode::ToString()
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
