#pragma once

#include "AbstractConstValueNode.cpp"

class FloatConstValueNode : public AbstractConstValueNode
{
   public:
    FloatConstValueNode(std::string value) : AbstractConstValueNode() { this->value = value; }

    std::string GetValue() { return this->value; };

    virtual std::string ToString() override { return GetValue(); }

   private:
    std::string value;
};