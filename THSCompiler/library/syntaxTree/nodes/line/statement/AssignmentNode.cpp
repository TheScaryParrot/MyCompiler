#pragma once

#include "AbstractStatementNode.cpp"

#include "assignOperators/EAssignOperators.cpp"

/// @brief This node is used for assign statements without a value (++ and --). See ValueAssignmentNode.cpp for assign statements with a value.
class AssignmentNode : public AbstractStatementNode
{
public:
    AssignmentNode(std::string variableName, EAssignOperators assignOperator);
    virtual ~AssignmentNode();

    virtual std::string ToString() override;

private:
    std::string variableName;
    EAssignOperators assignOperator;
};

AssignmentNode::AssignmentNode(std::string variableName, EAssignOperators assignOperator) : AbstractStatementNode()
{
    this->variableName = variableName;
    this->assignOperator = assignOperator;
}

AssignmentNode::~AssignmentNode()
{
}

std::string AssignmentNode::ToString()
{
    return variableName + EAssignOperatorsToString(assignOperator);
}