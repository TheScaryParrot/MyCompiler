#pragma once

#include <memory>
#include <vector>

#include "AbstractLineNode.cpp"

class CodeblockNode : AbstractTreeNode
{
   public:
    void AddCodeline(AbstractLineNode* line);
    AbstractLineNode* GetLine(int index);
    unsigned int GetLineCount();

    std::string ToString();

   private:
    std::vector<std::unique_ptr<AbstractLineNode>> lines;
};

void CodeblockNode::AddCodeline(AbstractLineNode* codeLine)
{
    lines.push_back(std::unique_ptr<AbstractLineNode>(codeLine));
}

AbstractLineNode* CodeblockNode::GetLine(int index) { return lines[index].get(); }

unsigned int CodeblockNode::GetLineCount() { return lines.size(); }

std::string CodeblockNode::ToString()
{
    std::string result = "{\n";

    for (std::unique_ptr<AbstractLineNode>& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}