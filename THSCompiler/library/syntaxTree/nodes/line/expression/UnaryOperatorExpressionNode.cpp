#pragma once

#include "AbstractExpressionNode.cpp"
#include "operators/EUnaryOperators.cpp"

class UnaryOperatorExpressionNode : public AbstractExpressionNode
{
   public:
    UnaryOperatorExpressionNode(EPreUnaryOperators preUnaryOperator, AbstractExpressionNode* value,
                                EPostUnaryOperators postUnaryOperator);
    ~UnaryOperatorExpressionNode();

    virtual std::string ToString() override;

   private:
    EPreUnaryOperators preUnaryOperator;
    AbstractExpressionNode* value;
    EPostUnaryOperators postUnaryOperator;
};

UnaryOperatorExpressionNode::UnaryOperatorExpressionNode(EPreUnaryOperators preUnaryOperator,
                                                         AbstractExpressionNode* value,
                                                         EPostUnaryOperators postUnaryOperator)
    : AbstractExpressionNode()
{
    this->preUnaryOperator = preUnaryOperator;
    this->value = value;
    this->postUnaryOperator = postUnaryOperator;
}

UnaryOperatorExpressionNode::~UnaryOperatorExpressionNode() { delete value; }

std::string UnaryOperatorExpressionNode::ToString()
{
    return EPreUnaryOperatorsToString(preUnaryOperator) + value->ToString() +
           EPostUnaryOperatorsToString(postUnaryOperator);
}
