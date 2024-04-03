#pragma once

#include "../CodeblockNode.cpp"

class BodyNode : AbstractTreeNode
{
public:
    BodyNode();
    BodyNode(CodeblockNode* codeblockNode);
    ~BodyNode();

    void AddCodeLine(AbstractLineNode* codeLine);

    virtual std::string ToString() override;

private:
    CodeblockNode* codeblockNode;
};

BodyNode::BodyNode() : AbstractTreeNode()
{
    this->codeblockNode = new CodeblockNode();
}

BodyNode::BodyNode(CodeblockNode* codeblockNode) : AbstractTreeNode()
{
    this->codeblockNode = codeblockNode;
}

BodyNode::~BodyNode()
{
    delete codeblockNode;
}

void BodyNode::AddCodeLine(AbstractLineNode* codeLine)
{
    codeblockNode->AddCodeline(codeLine);
}

std::string BodyNode::ToString()
{
    return "Body: " + codeblockNode->ToString();
}