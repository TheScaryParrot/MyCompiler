#pragma once

#include "../../../../AbstractTreeNode.cpp"

class TypeNode : public AbstractTreeNode
{
public:
    TypeNode(std::string name);
    TypeNode() = default;
    ~TypeNode();

    std::string GetIdentfier();

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

std::string TypeNode::GetIdentfier()
{
    return name;
}

std::string TypeNode::ToString()
{
    return name;
}