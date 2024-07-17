#pragma once

#include "AbstractValueNode.cpp"

class ParenthesisExpressionNode : public AbstractValueNode
{
   public:
    AbstractExpressionNode* expression;

    ParenthesisExpressionNode(AbstractExpressionNode* expression) : AbstractValueNode() { this->expression = expression; }

    virtual std::string ToString() override { return "(" + expression->ToString() + ")"; }
};
