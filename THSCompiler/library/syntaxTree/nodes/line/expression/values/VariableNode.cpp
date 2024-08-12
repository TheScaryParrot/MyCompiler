#pragma once

#include <vector>

#include "AbstractValueNode.cpp"

class VariableNode : public AbstractValueNode
{
   public:
    VariableNode(std::vector<std::string> ids) { this->ids = ids; }

    virtual bool RequiresAXRegister() override { return false; }

    virtual std::string ToString() override
    {
        std::string result = ids[0];

        for (size_t i = 1; i < ids.size(); i++)
        {
            result += "." + ids[i];
        }

        return result;
    }

    std::vector<std::string> ids;
};