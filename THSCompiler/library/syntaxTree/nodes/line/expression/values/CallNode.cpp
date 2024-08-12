#pragma once

#include <string>
#include <vector>

#include "AbstractValueNode.cpp"

class CallNode : public AbstractValueNode
{
   public:
    CallNode(std::string functionName, std::vector<AbstractExpressionNode*> arguments)
    {
        this->functionName = functionName;
        this->arguments = arguments;
    }

    ~CallNode()
    {
        for (AbstractExpressionNode* argument : arguments)
        {
            delete argument;
        }
    }

    virtual bool RequiresAXRegister() override { return true; }

    virtual std::string ToString() override
    {
        std::string result = functionName + "(";

        for (AbstractExpressionNode* argument : arguments)
        {
            result += argument->ToString() + ", ";
        }

        return result + ")";
    }

    std::string functionName;
    std::vector<AbstractExpressionNode*> arguments;
};
