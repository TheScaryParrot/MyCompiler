#pragma once

#include "AbstractConstValueNode.cpp"

class IntConstValueNode : public AbstractConstValueNode
{
   public:
    IntConstValueNode(int value) : AbstractConstValueNode() { this->value = value; }

    int GetValue() { return this->value; }

    virtual std::string ToString() override { return std::to_string(GetValue()); }

   private:
    int value;
};