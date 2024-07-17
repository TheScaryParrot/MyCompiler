#pragma once

#include "../../BodyCodeNode.cpp"
#include "../statement/AbstractStatementNode.cpp"

class BodyNode : public AbstractStatementNode
{
   public:
    BodyNode();
    BodyNode(BodyCodeNode* BodyCodeNode);
    ~BodyNode();

    void AddCodeLine(AbstractLineNode* codeLine);

    BodyCodeNode* GetCodeBlock();

    virtual std::string ToString() override;

   private:
    BodyCodeNode* bodyCodeNode;
};

BodyNode::BodyNode() : AbstractStatementNode() { this->bodyCodeNode = new BodyCodeNode(); }

BodyNode::BodyNode(BodyCodeNode* bodyCodeNode) : AbstractStatementNode() { this->bodyCodeNode = bodyCodeNode; }

BodyNode::~BodyNode() { delete bodyCodeNode; }

void BodyNode::AddCodeLine(AbstractLineNode* codeLine) { bodyCodeNode->AddLine(codeLine); }

BodyCodeNode* BodyNode::GetCodeBlock() { return bodyCodeNode; }

std::string BodyNode::ToString() { return bodyCodeNode->ToString(); }