#pragma once

#include "AbstractConstValueNode.cpp"

class FloatConstValueNode : public AbstractConstValueNode
{
   public:
    FloatConstValueNode(float value) : AbstractConstValueNode() { this->value = value; }

    float GetValue() { return this->value; };

    virtual std::string ToString() override { return std::to_string(GetValue()); }

   private:
    float value;
};