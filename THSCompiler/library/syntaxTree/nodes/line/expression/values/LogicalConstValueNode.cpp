#pragma once

#include "AbstractConstValueNode.cpp"

class LogicalConstValueNode : public AbstractConstValueNode
{
public:
    LogicalConstValueNode(bool value);
    ~LogicalConstValueNode();

    bool GetValue();

    virtual std::string ToString() override;

private:
    bool value;
};

LogicalConstValueNode::LogicalConstValueNode(bool value) : AbstractConstValueNode()
{
    this->value = value;
}

LogicalConstValueNode::~LogicalConstValueNode()
{
}

bool LogicalConstValueNode::GetValue()
{
    return value;
}

std::string LogicalConstValueNode::ToString()
{
    return value ? "true" : "false";
}