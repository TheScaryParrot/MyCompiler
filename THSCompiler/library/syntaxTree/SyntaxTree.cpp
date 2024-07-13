#pragma once

#include <iostream>

#include "nodes/line/CodeblockNode.cpp"

class SyntaxTree
{
   public:
    SyntaxTree();
    ~SyntaxTree();

    void AddCodeLineNode(AbstractLineNode* codeLine);

    CodeblockNode* GetCodeBlock();

    std::string ToString();

   private:
    CodeblockNode* codeBlock = new CodeblockNode();
};

SyntaxTree::SyntaxTree() {}

SyntaxTree::~SyntaxTree() { delete codeBlock; }

void SyntaxTree::AddCodeLineNode(AbstractLineNode* codeLine) { codeBlock->AddCodeline(codeLine); }

CodeblockNode* SyntaxTree::GetCodeBlock() { return codeBlock; }

std::string SyntaxTree::ToString() { return "SyntaxTree: " + codeBlock->ToString(); }