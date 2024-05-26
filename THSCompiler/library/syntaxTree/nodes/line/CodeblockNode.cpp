#pragma once

#include <vector>
#include <memory>

#include "AbstractLineNode.cpp"


class CodeblockNode : AbstractTreeNode
{
public:
    CodeblockNode();
    ~CodeblockNode();

    void AddCodeline(AbstractLineNode* line);
    AbstractLineNode* GetLine(int index);
    unsigned int GetLineCount();

    std::string ToString();

private:
    std::vector<std::auto_ptr<AbstractLineNode>> lines;
};

CodeblockNode::CodeblockNode()
{
}

void CodeblockNode::AddCodeline(AbstractLineNode* codeLine)
{
    lines.push_back(std::auto_ptr<AbstractLineNode>(codeLine));
}

AbstractLineNode* CodeblockNode::GetLine(int index)
{
    return lines[index].get();
}

unsigned int CodeblockNode::GetLineCount()
{
    return lines.size();
}

std::string CodeblockNode::ToString()
{
    std::string result = "{\n";

    for (std::auto_ptr<AbstractLineNode> line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}