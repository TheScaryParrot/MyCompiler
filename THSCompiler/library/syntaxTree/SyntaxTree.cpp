#pragma once

#include "nodes/line/CodeblockNode.cpp"

#include <iostream>

class SyntaxTree
{
public: 
    SyntaxTree();
    ~SyntaxTree();

    void AddCodeLineNode(AbstractLineNode* codeLine);
    AbstractLineNode* GetLine(int index);
    unsigned int GetLineCount();

    CodeblockNode* GetCodeBlock();

    std::string ToString();

private:
    CodeblockNode* codeBlock = new CodeblockNode();
};

SyntaxTree::SyntaxTree()
{
}

SyntaxTree::~SyntaxTree()
{
    delete codeBlock;
}

void SyntaxTree::AddCodeLineNode(AbstractLineNode* codeLine)
{
    codeBlock->AddCodeline(codeLine);
}

AbstractLineNode* SyntaxTree::GetLine(int index)
{
    return codeBlock->GetLine(index);
}

unsigned int SyntaxTree::GetLineCount()
{
    return codeBlock->GetLineCount();
}

CodeblockNode* SyntaxTree::GetCodeBlock()
{
    return codeBlock;
}

std::string SyntaxTree::ToString()
{
    return "SyntaxTree: " + codeBlock->ToString();
}