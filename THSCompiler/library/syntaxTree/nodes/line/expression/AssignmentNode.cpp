#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"
#include "operators/EAssignOperators.cpp"
#include "values/VariableNode.cpp"

class Assignment
{
   public:
    Assignment(VariableNode* L_value, EAssignOperators assignOperator)
    {
        this->L_value = L_value;
        this->assignOperator = assignOperator;
    }

    ~Assignment() { delete L_value; }

    VariableNode* L_value;
    EAssignOperators assignOperator;
};

class AssignmentNode : public AbstractExpressionNode
{
   public:
    virtual ~AssignmentNode();

    virtual std::string ToString() override;

    std::vector<Assignment*> assignments;
    AbstractExpressionNode* value;
};

AssignmentNode::~AssignmentNode()
{
    for (auto& assignment : assignments) delete assignment;

    delete value;
}

std::string AssignmentNode::ToString()
{
    std::string result = "";

    for (Assignment* assignment : assignments)
    {
        result += assignment->L_value->ToString() + " " + EAssignOperatorsToString(assignment->assignOperator) + " ";
    }

    return result + value->ToString();
}