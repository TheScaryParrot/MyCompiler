#pragma once

#include <iostream>
#include <vector>

#include "../AbstractValueNode.cpp"

class ValueChainNode : public AbstractValueNode
{
   public:
    virtual ~ValueChainNode();

    ValueChainNode* AddPropertyAccess(AbstractExpressionNode* value);

    virtual std::string ToString() override;

    std::vector<AbstractExpressionNode*> propertyAccesses;
};

ValueChainNode::~ValueChainNode()
{
    for (AbstractExpressionNode* property : propertyAccesses)
    {
        delete property;
    }
}

ValueChainNode* ValueChainNode::AddPropertyAccess(AbstractExpressionNode* value)
{
    propertyAccesses.push_back(value);

    return this;
}

std::string ValueChainNode::ToString()
{
    std::string result = propertyAccesses[0]->ToString();

    for (size_t i = 1; i < propertyAccesses.size(); i++)
    {
        result += ".";
        result += propertyAccesses[i]->ToString();
    }

    return result;
}
