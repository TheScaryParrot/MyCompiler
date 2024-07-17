#pragma once

#include "AbstractConstValueNode.cpp"

class IntConstValueNode : public AbstractConstValueNode
{
   public:
    IntConstValueNode(std::string value) : AbstractConstValueNode() { this->value = value; }

    std::string GetValue() { return this->value; }

    virtual std::string ToString() override { return GetValue(); }

   private:
    std::string value;
};