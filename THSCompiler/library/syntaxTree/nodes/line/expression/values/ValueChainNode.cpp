#pragma once

#include <vector>
#include <iostream>

#include "../AbstractValueNode.cpp"

class ValueChainNode : public AbstractValueNode
{
public:
    ValueChainNode(AbstractExpressionNode* baseValue);
    virtual ~ValueChainNode();

    ValueChainNode* AddPropertyAccess(AbstractExpressionNode* value, bool isStaticAccess);

    virtual std::string ToString() override;

private:
    typedef struct {
        bool isStaticAccess;
        AbstractExpressionNode* value;
    } PropertyAccess;

    AbstractExpressionNode* baseValue;
    std::vector<PropertyAccess> propertyAccesses;
};

ValueChainNode::ValueChainNode(AbstractExpressionNode* baseValue) : AbstractValueNode()
{
    this->baseValue = baseValue;
}

ValueChainNode::~ValueChainNode()
{
    delete baseValue;

    for (PropertyAccess property : propertyAccesses)
    {
        delete property.value;
    }
}

ValueChainNode* ValueChainNode::AddPropertyAccess(AbstractExpressionNode* value, bool isStaticAccess)
{
    PropertyAccess propertyAccess = {isStaticAccess, value};
    propertyAccesses.push_back(propertyAccess);

    return this;
}

std::string ValueChainNode::ToString()
{
    std::string result = baseValue->ToString();

    for (PropertyAccess property : propertyAccesses)
    {
        result += property.isStaticAccess ? ":" : ".";
        result += property.value->ToString();
    }

    return result;
}
