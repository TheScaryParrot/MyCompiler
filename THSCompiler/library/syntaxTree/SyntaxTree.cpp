#pragma once

#include "nodes/line/CodeLineNode.cpp"

#include <vector>

class SyntaxTree
{
public: 
    SyntaxTree();
    ~SyntaxTree();

    void AddCodeLineNode(CodeLineNode* codeLine);

    std::string ToString();

private:
    std::vector<CodeLineNode*> codeLines;
};

SyntaxTree::SyntaxTree()
{
}

SyntaxTree::~SyntaxTree()
{
    for (CodeLineNode* codeLine : codeLines)
    {
        delete codeLine;
    }
}

void SyntaxTree::AddCodeLineNode(CodeLineNode* codeLine)
{
    codeLines.push_back(codeLine);
}

std::string SyntaxTree::ToString()
{
    std::string result = "SyntaxTree: {\n";

    for (CodeLineNode* codeLine : codeLines)
    {
        result += "\t" + codeLine->ToString() + "\n";
    }

    result += "}";

    return result;
}