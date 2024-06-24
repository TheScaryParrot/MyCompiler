#pragma once

#include "../CodeblockNode.cpp"
#include "../statement/AbstractStatementNode.cpp"

class BodyNode : public AbstractStatementNode
{
   public:
    BodyNode();
    BodyNode(CodeblockNode* codeblockNode);
    ~BodyNode();

    void AddCodeLine(AbstractLineNode* codeLine);

    CodeblockNode* GetCodeBlock();

    virtual std::string ToString() override;

   private:
    CodeblockNode* codeblockNode;
};

BodyNode::BodyNode() : AbstractStatementNode() { this->codeblockNode = new CodeblockNode(); }

BodyNode::BodyNode(CodeblockNode* codeblockNode) : AbstractStatementNode() { this->codeblockNode = codeblockNode; }

BodyNode::~BodyNode() { delete codeblockNode; }

void BodyNode::AddCodeLine(AbstractLineNode* codeLine) { codeblockNode->AddCodeline(codeLine); }

CodeblockNode* BodyNode::GetCodeBlock() { return codeblockNode; }

std::string BodyNode::ToString() { return codeblockNode->ToString(); }