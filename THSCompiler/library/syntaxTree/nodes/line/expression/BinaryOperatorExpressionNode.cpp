#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"
#include "operators/OperatorExpressionPair.cpp"

class BinaryOperatorExpressionNode : public AbstractExpressionNode
{
   public:
    BinaryOperatorExpressionNode(AbstractExpressionNode* firstExpression, std::vector<OperatorExpressionPair*> operatorExpressionPairs)
        : AbstractExpressionNode()
    {
        this->firstExpression = firstExpression;
        this->operatorExpressionPairs = operatorExpressionPairs;
    }
    ~BinaryOperatorExpressionNode()
    {
        delete firstExpression;

        for (OperatorExpressionPair* pair : operatorExpressionPairs)
        {
            delete pair;
        }
    }

    virtual bool RequiresAXRegister() override { return true; }

    virtual std::string ToString() override
    {
        std::string result = firstExpression->ToString();

        for (OperatorExpressionPair* pair : operatorExpressionPairs)
        {
            result += pair->ToString();
        }

        return result;
    }

    AbstractExpressionNode* firstExpression;
    std::vector<OperatorExpressionPair*> operatorExpressionPairs;
};
