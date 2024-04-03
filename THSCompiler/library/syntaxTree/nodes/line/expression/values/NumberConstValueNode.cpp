#pragma once

#include "AbstractConstValueNode.cpp"

class NumberConstValueNode : public AbstractConstValueNode
{
public:
    NumberConstValueNode(std::string value);
    ~NumberConstValueNode();

    std::string GetValue();

    virtual std::string ToString() override;

private:
    std::string value;
};

NumberConstValueNode::NumberConstValueNode(std::string value) : AbstractConstValueNode()
{
    this->value = value;
}

NumberConstValueNode::~NumberConstValueNode()
{
}

std::string NumberConstValueNode::GetValue()
{
    return this->value;
}

std::string NumberConstValueNode::ToString()
{
    return GetValue();
}