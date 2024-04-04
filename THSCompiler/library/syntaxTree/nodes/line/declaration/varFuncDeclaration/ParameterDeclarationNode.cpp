#pragma once

#include "../../../AbstractTreeNode.cpp"

class ParameterDeclarationNode : public AbstractTreeNode
{
public:
    ParameterDeclarationNode(std::string type, std::string name);
    ~ParameterDeclarationNode();

    virtual std::string ToString() override;

private:
    std::string name;
    std::string type;
};

ParameterDeclarationNode::ParameterDeclarationNode(std::string type, std::string name) : AbstractTreeNode()
{
    this->type = type;
    this->name = name;
}

ParameterDeclarationNode::~ParameterDeclarationNode()
{
}

std::string ParameterDeclarationNode::ToString()
{
    return "param: " + type + " " + name;
}