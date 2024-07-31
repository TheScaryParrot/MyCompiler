#pragma once

#include <memory>
#include <vector>

#include "line/AbstractLineNode.cpp"

class GlobalCodeNode : AbstractTreeNode
{
   public:
    void AddLineNode(AbstractLineNode* line);
    AbstractLineNode* GetLine(int index);
    unsigned int GetLineCount();

    std::string ToString();

   private:
    std::vector<std::unique_ptr<AbstractLineNode>> lines;
};

void GlobalCodeNode::AddLineNode(AbstractLineNode* codeLine) { lines.push_back(std::unique_ptr<AbstractLineNode>(codeLine)); }

AbstractLineNode* GlobalCodeNode::GetLine(int index) { return lines[index].get(); }

unsigned int GlobalCodeNode::GetLineCount() { return lines.size(); }

std::string GlobalCodeNode::ToString()
{
    std::string result = "{\n";

    for (std::unique_ptr<AbstractLineNode>& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}