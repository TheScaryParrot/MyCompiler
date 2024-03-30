#pragma once

#include "../../../AbstractTreeNode.cpp"

class ParameterDeclarationNode : public AbstractTreeNode
{
public:
    ParameterDeclarationNode(std::string name);
    ~ParameterDeclarationNode();

    virtual std::string ToString() override;

private:
    std::string name;
    //TODO Add type
};

ParameterDeclarationNode::ParameterDeclarationNode(std::string name) : AbstractTreeNode()
{
    this->name = name;
}

ParameterDeclarationNode::~ParameterDeclarationNode()
{
}

std::string ParameterDeclarationNode::ToString()
{
    return "param: TYPE " + name;
}