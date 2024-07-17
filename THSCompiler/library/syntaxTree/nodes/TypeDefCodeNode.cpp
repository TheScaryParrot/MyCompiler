#pragma once

#include <memory>
#include <vector>

#include "line/declaration/PropertyDeclarationNode.cpp"

class GlobalCodeNode : AbstractTreeNode
{
   public:
    void AddCodeline(PropertyDeclarationNode* line);
    PropertyDeclarationNode* GetLine(int index);
    unsigned int GetLineCount();

    std::string ToString();

   private:
    std::vector<std::unique_ptr<PropertyDeclarationNode>> lines;
};

void GlobalCodeNode::AddCodeline(PropertyDeclarationNode* codeLine) { lines.push_back(std::unique_ptr<PropertyDeclarationNode>(codeLine)); }

PropertyDeclarationNode* GlobalCodeNode::GetLine(int index) { return lines[index].get(); }

unsigned int GlobalCodeNode::GetLineCount() { return lines.size(); }

std::string GlobalCodeNode::ToString()
{
    std::string result = "{\n";

    for (std::unique_ptr<PropertyDeclarationNode>& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}