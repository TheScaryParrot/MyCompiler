#pragma once

#include "../AbstractTreeNode.cpp"
#include "AbstractLineChildNode.cpp"

class CodeLineNode : public AbstractTreeNode
{
public:
    CodeLineNode(AbstractLineChildNode* lineChild);
    ~CodeLineNode();

    virtual std::string ToString() override;

private:
    AbstractLineChildNode* lineChild;
};

CodeLineNode::CodeLineNode(AbstractLineChildNode* lineChild) : AbstractTreeNode()
{
    this->lineChild = lineChild;
}

CodeLineNode::~CodeLineNode()
{
    delete lineChild;
}

std::string CodeLineNode::ToString()
{
    return lineChild->ToString();
}