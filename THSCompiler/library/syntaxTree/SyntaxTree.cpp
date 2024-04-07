#pragma once

#include "nodes/line/CodeblockNode.cpp"

#include <iostream>

class SyntaxTree
{
public: 
    SyntaxTree();
    ~SyntaxTree();

    void AddCodeLineNode(AbstractLineNode* codeLine);

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

std::string SyntaxTree::ToString()
{
    return "SyntaxTree: " + codeBlock->ToString();
}