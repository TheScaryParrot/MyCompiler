#pragma once

#include "../AbstractExpressionNode.cpp"

class CallArgument
{
public:
    CallArgument(AbstractExpressionNode* argumentValue);
    ~CallArgument();

    std::string ToString();


private:
    AbstractExpressionNode* argumentValue;
};

CallArgument::CallArgument(AbstractExpressionNode* argumentValue)
{
    this->argumentValue = argumentValue;
}

CallArgument::~CallArgument()
{
    delete argumentValue;
}

std::string CallArgument::ToString()
{
    return argumentValue->ToString();
}