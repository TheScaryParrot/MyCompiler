#pragma once

#include "AbstractConstValueNode.cpp"

class StringConstValueNode : public AbstractConstValueNode
{
   public:
    StringConstValueNode(std::string value) : AbstractConstValueNode() { this->value = value; }

    std::string GetValue() { return value; }

    virtual std::string ToString() override { return '"' + GetValue() + '"'; }

   private:
    std::string value;
};