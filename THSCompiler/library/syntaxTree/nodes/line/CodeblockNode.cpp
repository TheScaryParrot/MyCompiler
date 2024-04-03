#pragma once

#include <vector>

#include "AbstractLineNode.cpp"


class CodeblockNode : AbstractTreeNode
{
public:
    CodeblockNode();
    ~CodeblockNode();

    void AddCodeline(AbstractLineNode* line);

    std::string ToString();

private:
    std::vector<AbstractLineNode*> lines;

};

CodeblockNode::CodeblockNode()
{
}

CodeblockNode::~CodeblockNode()
{
    for (AbstractLineNode* line : lines)
    {
        delete line;
    }
}

void CodeblockNode::AddCodeline(AbstractLineNode* codeLine)
{
    lines.push_back(codeLine);
}

std::string CodeblockNode::ToString()
{
    std::string result = "{\n";

    for (AbstractLineNode* line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}