#pragma once

#include <iostream>
#include <vector>

#include "../AbstractValueNode.cpp"

class StaticValueChainNode : public AbstractValueNode
{
   public:
    virtual ~StaticValueChainNode();

    StaticValueChainNode* AddPropertyAccess(AbstractExpressionNode* value);

    virtual std::string ToString() override;

    std::vector<AbstractExpressionNode*> propertyAccesses;
};

StaticValueChainNode::~StaticValueChainNode()
{
    for (AbstractExpressionNode* property : propertyAccesses)
    {
        delete property;
    }
}

StaticValueChainNode* StaticValueChainNode::AddPropertyAccess(AbstractExpressionNode* value)
{
    propertyAccesses.push_back(value);

    return this;
}

std::string StaticValueChainNode::ToString()
{
    std::string result = propertyAccesses[0]->ToString();

    for (size_t i = 1; i < propertyAccesses.size(); i++)
    {
        result += ":";
        result += propertyAccesses[i]->ToString();
    }

    return result;
}
