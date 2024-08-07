#pragma once

#include <vector>

#include "AbstractValueNode.cpp"

class StructNode : public AbstractValueNode
{
   public:
    std::vector<AbstractExpressionNode*> values;

    StructNode(std::vector<AbstractExpressionNode*> values) : AbstractValueNode() { this->values = values; }

    ~StructNode()
    {
        for (auto value : values)
        {
            delete value;
        }
    }

    virtual std::string ToString() override
    {
        std::string result = "{";
        for (auto value : values)
        {
            result += value->ToString() + ", ";
        }
        result += "}";
        return result;
    }
};