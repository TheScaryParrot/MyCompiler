#pragma once

#include <vector>

#include "../AbstractValueNode.cpp"

#include "CallArgument.cpp"

class CallNode : public AbstractValueNode
{
public:
    CallNode(std::string functionName, std::vector<CallArgument*> arguments);
    ~CallNode();

    virtual std::string ToString() override;

private:
    std::string functionName;
    std::vector<CallArgument*> arguments;
};

CallNode::CallNode(std::string functionName, std::vector<CallArgument*> arguments) : AbstractValueNode()
{
    this->functionName = functionName;
    this->arguments = arguments;
}

CallNode::~CallNode()
{
    for (CallArgument* argument : arguments)
    {
        delete argument;
    }
}

std::string CallNode::ToString()
{
    std::string result = functionName + "(";

    for (CallArgument* argument : arguments)
    {
        result += argument->ToString() + ", ";
    }

    return result + ");";
}