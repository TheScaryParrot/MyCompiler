#pragma once

#include "AbstractConstValueNode.cpp"

class LogicalConstValueNode : public AbstractConstValueNode
{
   public:
    LogicalConstValueNode(bool value) : AbstractConstValueNode() { this->value = value; };

    bool GetValue() { return value; };

    virtual std::string ToString() override { return value ? "true" : "false"; };

   private:
    bool value;
};