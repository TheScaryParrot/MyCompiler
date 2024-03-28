#pragma once

#include "grammarPatterns/start/CodeBlock.cpp"
#include "../tokens/TokenList.cpp"

class SyntaxTree
{
public: 
    SyntaxTree(TokenList* tokens);
    ~SyntaxTree();

    std::string ToString();

private:
    CodeBlock* codeBlock;

    void Parse(TokenList* tokens);
};

SyntaxTree::SyntaxTree(TokenList* tokens)
{
    Parse(tokens);
}

SyntaxTree::~SyntaxTree()
{
    delete codeBlock;
}

std::string SyntaxTree::ToString()
{
    return codeBlock->ToString();
}

void SyntaxTree::Parse(TokenList* tokens)
{
    codeBlock = CodeBlock::Parse(tokens);
}