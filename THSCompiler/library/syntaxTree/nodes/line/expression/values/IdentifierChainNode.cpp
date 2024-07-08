#pragma once

#include <iostream>
#include <vector>

#include "../AbstractValueNode.cpp"

class IdentifierChainNode : public AbstractValueNode
{
   public:
    IdentifierChainNode(bool isStatic);
    virtual ~IdentifierChainNode();

    IdentifierChainNode* AddPropertyAccess(AbstractExpressionNode* value);

    virtual std::string ToString() override;

    std::vector<AbstractExpressionNode*> propertyAccesses;
};

IdentifierChainNode::~IdentifierChainNode()
{
    for (AbstractExpressionNode* property : propertyAccesses)
    {
        delete property;
    }
}

IdentifierChainNode* IdentifierChainNode::AddPropertyAccess(AbstractExpressionNode* value)
{
    propertyAccesses.push_back(value);

    return this;
}

std::string IdentifierChainNode::ToString()
{
    std::string result = propertyAccesses[0]->ToString();

    for (size_t i = 1; i < propertyAccesses.size(); i++)
    {
        result += ".";
        result += propertyAccesses[i]->ToString();
    }

    return result;
}
