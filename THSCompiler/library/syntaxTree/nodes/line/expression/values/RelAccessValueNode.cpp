#pragma once

#include <vector>

#include "AbstractValueNode.cpp"

struct RelAccess
{
    AbstractExpressionNode* value;
    bool isStaticAccess;
};

class RelAccessValueNode : public AbstractValueNode
{
   public:
    virtual ~RelAccessValueNode();

    void SetLastValue(AbstractExpressionNode* value);
    void AddRelAccess(RelAccess relAccess);

    virtual std::string ToString() override;

    AbstractExpressionNode* lastValue;
    std::vector<RelAccess> relAccesses;
};

RelAccessValueNode::~RelAccessValueNode()
{
    delete lastValue;

    for (RelAccess relAccess : relAccesses)
    {
        delete relAccess.value;
    }
}

void RelAccessValueNode::SetLastValue(AbstractExpressionNode* value) { lastValue = value; }

void RelAccessValueNode::AddRelAccess(RelAccess relAccess) { relAccesses.push_back(relAccess); }

std::string RelAccessValueNode::ToString()
{
    std::string result = "";

    for (RelAccess relAccess : relAccesses)
    {
        result += relAccess.value->ToString() + (relAccess.isStaticAccess ? ":" : ".");
    }

    return result + lastValue->ToString();
}