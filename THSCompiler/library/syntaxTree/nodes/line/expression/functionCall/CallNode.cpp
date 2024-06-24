#pragma once

#include <vector>

#include "../AbstractValueNode.cpp"

class CallNode : public AbstractValueNode
{
public:
    CallNode(std::string functionName, std::vector<AbstractExpressionNode *> arguments);
    ~CallNode();

    virtual std::string ToString() override;

    std::string functionName;
    std::vector<AbstractExpressionNode *> arguments;
};

CallNode::CallNode(std::string functionName, std::vector<AbstractExpressionNode *> arguments) : AbstractValueNode()
{
    this->functionName = functionName;
    this->arguments = arguments;
}

CallNode::~CallNode()
{
    for (AbstractExpressionNode *argument : arguments)
    {
        delete argument;
    }
}

std::string CallNode::ToString()
{
    std::string result = functionName + "(";

    for (AbstractExpressionNode *argument : arguments)
    {
        result += argument->ToString() + ", ";
    }

    return result + ");";
}