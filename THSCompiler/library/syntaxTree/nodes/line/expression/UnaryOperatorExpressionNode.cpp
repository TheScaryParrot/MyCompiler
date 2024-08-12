#pragma once

#include "AbstractExpressionNode.cpp"
#include "operators/EUnaryOperators.cpp"

class UnaryOperatorExpressionNode : public AbstractExpressionNode
{
   public:
    UnaryOperatorExpressionNode(EPreUnaryOperators preUnaryOperator, AbstractExpressionNode* value, EPostUnaryOperators postUnaryOperator,
                                bool applyToReference)
        : AbstractExpressionNode()
    {
        this->preUnaryOperator = preUnaryOperator;
        this->value = value;
        this->postUnaryOperator = postUnaryOperator;
    }

    ~UnaryOperatorExpressionNode() { delete value; }

    virtual bool RequiresAXRegister() override { return false; }

    virtual std::string ToString() override
    {
        return EPreUnaryOperatorsToString(preUnaryOperator) + value->ToString() + EPostUnaryOperatorsToString(postUnaryOperator);
    }

    EPreUnaryOperators preUnaryOperator;
    AbstractExpressionNode* value;
    EPostUnaryOperators postUnaryOperator;
    ///@brief Whether the operator should be applied to the reference of the value. For ++ this is true, for ! this is false
    bool applyToReference;
};
