#pragma once

#include "AssignmentNode.cpp"

#include "../expression/AbstractExpressionNode.cpp"
#include "assignOperators/EAssignOperators.cpp"

class ValueAssignmentNode : public AssignmentNode
{
public:
    ValueAssignmentNode(std::string variableName, EAssignOperators assignOperator, AbstractExpressionNode* expression);
    ~ValueAssignmentNode();

    virtual std::string ToString() override;

private:
    AbstractExpressionNode* expression;
};


ValueAssignmentNode::ValueAssignmentNode(std::string variableName, EAssignOperators assignOperator, AbstractExpressionNode* expression) : AssignmentNode(variableName, assignOperator)
{
    this->expression = expression;
}

ValueAssignmentNode::~ValueAssignmentNode()
{
    delete expression;
}

std::string ValueAssignmentNode::ToString()
{
    return this->AssignmentNode::ToString() + expression->ToString();
}