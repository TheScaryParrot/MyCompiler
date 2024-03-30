#pragma once

#include "../../../../AbstractTreeNode.cpp"

class TypeNode : public AbstractTreeNode
{
public:
    TypeNode(std::string name);
    TypeNode() = default;
    ~TypeNode();

    virtual std::string ToString() override;

protected:
    std::string name;
};

TypeNode::TypeNode(std::string name) : AbstractTreeNode()
{
    this->name = name;
}

TypeNode::~TypeNode()
{
}

std::string TypeNode::ToString()
{
    return "Type: " + name;
}