#pragma once

#include "AbstractConstValueNode.cpp"

class StringConstValueNode : public AbstractConstValueNode
{
   public:
    StringConstValueNode(std::string value);
    ~StringConstValueNode();

    std::string GetValue();

    virtual std::string ToString() override;

   private:
    std::string value;
};

StringConstValueNode::StringConstValueNode(std::string value) : AbstractConstValueNode() { this->value = value; }

StringConstValueNode::~StringConstValueNode() {}

std::string StringConstValueNode::GetValue() { return value; }

std::string StringConstValueNode::ToString() { return '"' + GetValue() + '"'; }