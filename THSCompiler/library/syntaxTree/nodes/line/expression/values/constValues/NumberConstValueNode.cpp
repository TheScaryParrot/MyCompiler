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

NumberConstValueNode::NumberConstValueNode(std::string value) : AbstractConstValueNode() { this->value = value; }

NumberConstValueNode::~NumberConstValueNode() {}

std::string NumberConstValueNode::GetValue()
{
    std::string valueString = this->value;
    return valueString;
}

std::string NumberConstValueNode::ToString()
{
    std::string value = GetValue();
    return value;
}