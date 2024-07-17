#pragma once

#include <memory>
#include <vector>

#include "line/declaration/AbstractDeclarationNode.cpp"

class GlobalCodeNode : AbstractTreeNode
{
   public:
    void AddCodeline(AbstractDeclarationNode* line);
    AbstractDeclarationNode* GetLine(int index);
    unsigned int GetLineCount();

    std::string ToString();

   private:
    std::vector<std::unique_ptr<AbstractDeclarationNode>> lines;
};

void GlobalCodeNode::AddCodeline(AbstractDeclarationNode* codeLine) { lines.push_back(std::unique_ptr<AbstractDeclarationNode>(codeLine)); }

AbstractDeclarationNode* GlobalCodeNode::GetLine(int index) { return lines[index].get(); }

unsigned int GlobalCodeNode::GetLineCount() { return lines.size(); }

std::string GlobalCodeNode::ToString()
{
    std::string result = "{\n";

    for (std::unique_ptr<AbstractDeclarationNode>& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}