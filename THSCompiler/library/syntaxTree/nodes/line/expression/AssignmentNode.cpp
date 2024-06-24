#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"

#include "operators/EAssignOperators.cpp"

class Assignment
{
public:
    Assignment(AbstractExpressionNode *L_value, EAssignOperators assignOperator)
    {
        this->L_value = L_value;
        this->assignOperator = assignOperator;
    }

    AbstractExpressionNode *L_value;
    EAssignOperators assignOperator;
};

class AssignmentNode : public AbstractExpressionNode
{
public:
    AssignmentNode(std::vector<Assignment *> assignments, AbstractExpressionNode *value);
    virtual ~AssignmentNode();

    virtual std::string ToString() override;

    std::vector<Assignment *> assignments;
    AbstractExpressionNode *value;
};

AssignmentNode::AssignmentNode(std::vector<Assignment *> assignments, AbstractExpressionNode *value) : AbstractExpressionNode()
{
    this->assignments = assignments;
    this->value = value;
}

AssignmentNode::~AssignmentNode()
{
    delete value;
}

std::string AssignmentNode::ToString()
{
    std::string result = "";

    for (Assignment *assignment : assignments)
    {
        result += assignment->L_value->ToString() + " " + EAssignOperatorsToString(assignment->assignOperator) + " ";
    }

    return result + value->ToString();
}